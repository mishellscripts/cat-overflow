

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/opencv/cv_image.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/dir_nav.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include <time.h>
#include <algorithm>


#include "eyeLike.h"
#include "constants.h"

// include different header files base on different OS
#if defined _MSC_VER
#include <direct.h>

#define file file
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif


using namespace dlib;
using namespace cv;
using namespace std;

//------------------------------------------------------------------------------------------------
// function prototypes
void make_directory(const string &output_dir);
std::vector<Mat> load_imgs(const string &input_dir, const string &file_type);
void write_imgs(const std::vector<Mat> &images,
                const string &output_dir,
                const string &video_id,
                const string &file_type);

void run(std::vector<Mat> &imgs, char *predictor);

cv::Rect dlib_rect_to_opencv_rect(const dlib::rectangle &rect);

//functions for draw delaunay_triangles
void draw_delaunay_triangles(std::vector<full_object_detection> &shapes, Mat &img);
void draw_delaunay(Mat &img, Subdiv2D &subdiv);
//string get_image_name(string name);

std::vector<Dual_Points> eye_pupils(
        Mat &image,
        const std::vector<cv::Rect> &faces,
        const std::vector<full_object_detection> &shapes);

void draw_eye_center(Mat &img, const std::vector<Dual_Points> &p);
void draw_head_posting(Mat &img, const std::vector<Dual_Points> &p);

//Head Pose Estimation
std::vector<Dual_Points> head_pose_estimation(std::vector<full_object_detection> &shapes, Mat &img);
//------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
    // check the command line argument
    if (argc != 4)
    {
        cout << "Call this program like this:" << endl;
        cout << "Linux: ./face_detection ./video_frames ./output_dir video_id" << endl;
        cout << "Windows: face_detection.exe .\\video_frames .\\output_dir video_id" << endl;
        cout << "\nYou can get the shape_predictor_68_face_landmarks.dat file from:\n";
        cout << "http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        return 0;
    }

    make_directory(argv[2]);    // make the output dir

    // load images to memory, if on images are read exit the program
    std::vector<Mat> images = load_imgs(argv[1], ".png");
    if (images.size() == 0)
    {
        return 1;
    }

    // start processing
    run(images, "shape_predictor_68_face_landmarks.dat");

    // store images to disk
    write_imgs(images, argv[2], argv[3], ".png");

    return 0;
}

//create a folder to store processed images
void make_directory(const string &output_dir)
{
#if defined _MSC_VER
        _mkdir(output_dir.c_str());
#elif defind __GNUC__
        mkdir(output_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
}

//input_dir: folder that stores all original images
//file_type: image format, ".png" is used
//return: vector of Mat (original images)
//uses dlib's get_files_in_directory_tree to get all the images files and load into a vector<Mat>
std::vector<Mat> load_imgs(const string &input_dir, const string &file_type)
{
    std::vector<dlib::file> files = get_files_in_directory_tree(input_dir, match_ending(".png"), 0);

    //std::sort(files.begin(), files.end());

    if (files.size() == 0)
    {
        cout << "No images found in " << input_dir << endl;
        return std::vector<Mat>(0);
    }
    std::vector<Mat> imgs;
    for (int i = 0; i < files.size(); i++)
    {
        imgs.push_back(imread(files[i].full_name()));
        //cout << files[i].full_name() << endl;
    }
    return imgs;

}

// images: processed images
// stores all the process images into the ourput_dir
void write_imgs(const std::vector<Mat> &images,
                const string &output_dir,
                const string &video_id,
                const string &file_type)
{
    try {
        for (int i = 0; i < images.size(); i++)
        {
            imwrite(output_dir + "/" + video_id + "." + to_string(i) + file_type, images[i]);
        }
    } catch (Exception &e) {
        cout << e.what() << endl;
    }

}

// imgs: original images as input, and will be modify after processing
// predictor: pretrain data from dlib that gets 68 face landmarks
// this function processes original images
void run(std::vector<Mat> &imgs, char *predictor)
{   
    time_t start = time(nullptr);   // get the initial time for calculate the time for processing

    // get face detector
    frontal_face_detector detector = get_frontal_face_detector();

    // load dlib's shape_predictor
    shape_predictor sp;
    deserialize(predictor) >> sp;

    // main loop
    // loop through all the images in the memory and process it one by one in order
    for (unsigned int i = 0; i < imgs.size(); i++)
    { 
        // conver opencv's Mat (data type for image) to dlib's image type
        cv_image<bgr_pixel> cimg(imgs[i]);

        // uses dlib's face detection find the faces in an image
        // stores the faces areas in a vector of rectangle
        std::vector<dlib::rectangle> dets = detector(cimg);     //faces

        // shapes stores 68 face landmarks for each face in an image
        std::vector<full_object_detection> shapes;
        for (unsigned int j = 0; j < dets.size(); j++)
        {
            full_object_detection shape = sp(cimg, dets[j]);
            shapes.push_back(shape);
        }

        // conver the dlib rectangle of faces' area to opencv rectangle for eye_detection
        std::vector<cv::Rect> cv_faces;
        for (int k = 0; k < dets.size(); k++)
        {
            cv_faces.push_back(dlib_rect_to_opencv_rect(dets[k]));
        }
        // calling eye_detection to detect they eyes in image
        // Dual_Points contains left eye (point1) and right eye (point2)
        std::vector<Dual_Points> eyes = eye_pupils(imgs[i], cv_faces, shapes);

        // detect head posting
        // gets two points for the facing direction
        // may change to use openface later
        std::vector<Dual_Points> heads = head_pose_estimation(shapes, imgs[i]);

        // draw to the image
        draw_delaunay_triangles(shapes, imgs[i]);
        draw_eye_center(imgs[i], eyes);
        draw_head_posting(imgs[i], heads);
    }
    // output the total time usage
    cout << "time: " << time(nullptr) - start << endl;
}

// return: Dual_Points -- left eye and right eye's location for each face in an image
// find eye pupils
// get the eye's region by using 68 face landmarks
std::vector<Dual_Points> eye_pupils(
                Mat &image,
                const std::vector<cv::Rect> &faces,
                const std::vector<full_object_detection> &shapes)
{
    std::vector<pair<Rect, Rect>> eyes_regions;
    for (const auto& shape : shapes)
    {
        pair<Rect, Rect> region;
        //left eye region
        int l_tlx = shape.part(36).x();
        int l_tly = shape.part(37).y() < shape.part(38).y() ? shape.part(37).y() : shape.part(38).y();
        int l_brx = shape.part(39).x();
        int l_bry = shape.part(41).y() > shape.part(40).y() ? shape.part(41).y() : shape.part(40).y();

        Rect left_eye(cv::Point2i(l_tlx, l_tly), cv::Point2i(l_brx, l_bry));

        //right eye region
        int r_tlx = shape.part(42).x();
        int r_tly = shape.part(43).y() < shape.part(44).y() ? shape.part(43).y() : shape.part(44).y();
        int r_brx = shape.part(45).x();
        int r_bry = shape.part(47).y() > shape.part(46).y() ? shape.part(47).y() : shape.part(46).y();

        Rect right_eye(cv::Point2i(r_tlx, r_tly), cv::Point2i(r_brx, r_bry));

        region = make_pair(left_eye, right_eye);
        eyes_regions.push_back(region);
    }
    return eye_detection(image, faces, eyes_regions);
}

// conver dlib rectangle to opencv Rect
cv::Rect dlib_rect_to_opencv_rect(const dlib::rectangle &rect)
{
    return cv::Rect(cv::Point2i(rect.left(), rect.top()), cv::Point2i(rect.right() + 1, rect.bottom() + 1));
}

// calculate delaunay triangle by using opencv::Subdiv2D
void draw_delaunay_triangles(std::vector<full_object_detection> &shapes, Mat &img)
{

    Size source_image_resolution;
    source_image_resolution = img.size();
    Rect rect(0, 0, source_image_resolution.width, source_image_resolution.height);

    for (int i = 0; i < shapes.size(); i++)
    {
        Subdiv2D subdiv(rect);
        for (int j = 0; j < shapes[i].num_parts(); j++)
        {
            subdiv.insert(Point2f(shapes[i].part(j).x(), shapes[i].part(j).y()));
        }
        draw_delaunay(img, subdiv);
    }
}

// draw the blue line triangles onto the image
void draw_delaunay(Mat &img, Subdiv2D &subdiv)
{
    Scalar delaunay_color(255, 0, 0);
    std::vector<Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    std::vector<Point> pt(3);
    Size size = img.size();
    Rect rect(0, 0, size.width, size.height);

    for (size_t i = 0; i < triangleList.size(); i++)
    {
        Vec6f t = triangleList[i];
        pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
        pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
        pt[2] = Point(cvRound(t[4]), cvRound(t[5]));

        // Draw rectangles completely inside the image.
        if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2]))
        {
            line(img, pt[0], pt[1], delaunay_color, 1, CV_AA, 0);
            line(img, pt[1], pt[2], delaunay_color, 1, CV_AA, 0);
            line(img, pt[2], pt[0], delaunay_color, 1, CV_AA, 0);
        }
    }
}

// calculate head posting
std::vector<Dual_Points> head_pose_estimation(std::vector<full_object_detection> &shapes, Mat &img)
{
    std::vector<std::vector<cv::Point2d>> faces;
    //std::vector<std::vector<cv::Point3d>> models;
    std::vector<cv::Point3d> model;
    model.push_back(cv::Point3d(0.0f, 0.0f, 0.0f));
    model.push_back(cv::Point3d(0.0f, -330.0f, -65.0f));
    model.push_back(cv::Point3d(-225.0f, 170.0f, -135.0f));
    model.push_back(cv::Point3d(225.0f, 170.0f, -135.0f));
    model.push_back(cv::Point3d(-150.0f, -150.0f, -125.0f));
    model.push_back(cv::Point3d(150.0f, -150.0f, -125.0f));

    double focal_length = img.cols; //Approximate focal length
    Point2d center = cv::Point2d(img.cols / 2, img.rows / 2);
    cv::Mat camera_matrix;
    camera_matrix = (cv::Mat_<double>(3, 3) << focal_length, 0, center.x, 0, focal_length, center.y, 0, 0, 1);
    cv::Mat dist_coeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type); //assuming no lens distortion

    std::vector<Dual_Points> points;

    for (int i = 0; i < shapes.size(); i++)
    {
        faces.push_back(std::vector<cv::Point2d>(6));

        faces[i][0] = cv::Point2d(shapes[i].part(30).x(), shapes[i].part(30).y()); //Nose tip, 31
        faces[i][1] = cv::Point2d(shapes[i].part(8).x(), shapes[i].part(8).y());   //Chin, 9
        faces[i][2] = cv::Point2d(shapes[i].part(36).x(), shapes[i].part(36).y()); //Left eye left corner, 37
        faces[i][3] = cv::Point2d(shapes[i].part(45).x(), shapes[i].part(45).y()); //Right eye right corner, 46
        faces[i][4] = cv::Point2d(shapes[i].part(48).x(), shapes[i].part(48).y()); //Left mouth corner, 49
        faces[i][5] = cv::Point2d(shapes[i].part(54).x(), shapes[i].part(54).y()); //Right mouth corner, 55

        cv::Mat rotation_vector;
        cv::Mat translation_vector;

        cv::solvePnP(model, faces[i], camera_matrix, dist_coeffs, rotation_vector, translation_vector);

        std::vector<Point3d> nose_end_point3D;
        std::vector<Point2d> nose_end_point2D;
        nose_end_point3D.push_back(Point3d(0, 0, 500.0));

        projectPoints(nose_end_point3D, rotation_vector, translation_vector, camera_matrix, dist_coeffs, nose_end_point2D);

        //cv::line(img, faces[i][0], nose_end_point2D[0], cv::Scalar(0, 255, 0), 2);
        Dual_Points p;
        p.point1 = faces[i][0];
        p.point2 = nose_end_point2D[0];
        points.push_back(p);
/*
        cout << "Rotation Vector " << endl
             << rotation_vector << endl;
        cout << "Translation Vector " << endl
             << translation_vector << endl;
        cout << nose_end_point2D << endl;
*/
    }
    return points;
}

// draw small circle on eye pupils
void draw_eye_center(Mat &img, const std::vector<Dual_Points> &p)
{
    for (int i = 0; i < p.size(); i++)
    {
        cv::circle(img, p[i].point1, 3, cv::Scalar(255, 255, 255));
        cv::circle(img, p[i].point2, 3, cv::Scalar(255, 255, 255));
    }
}

// draw a line indicates the head posting
void draw_head_posting(Mat &img, const std::vector<Dual_Points> &p)
{
    for (int i = 0; i < p.size(); i++)
    {
        cv::line(img, p[i].point1, p[i].point2, cv::Scalar(0, 255, 0), 2);
    }
}
