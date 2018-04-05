#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/opencv/cv_image.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <time.h>

#include "eyeLike.h"
#include "constants.h"

#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif

using namespace dlib;
using namespace cv;
using namespace std;



string imgs_name(std::vector<string> &names, unsigned int num_frames, string first_frame);
std::vector<Mat> load_img(const std::vector<string> &names);

void run(std::vector<string> &imgs_name, std::vector<Mat> &imgs, char *predictor, const string folder_name);

cv::Rect dlib_rect_to_opencv_rect(const dlib::rectangle &rect);

//functions for draw delaunay_triangles
void draw_delaunay_triangles(std::vector<full_object_detection> &shapes, Mat &img);
void draw_delaunay(Mat &img, Subdiv2D &subdiv);
string get_image_name(string name);

void draw_eye_center(Mat &img, const std::vector<Dual_Points> &p);
void draw_head_posting(Mat &img, const std::vector<Dual_Points> &p);

//Head Pose Estimation
std::vector<Dual_Points> head_pose_estimation(std::vector<full_object_detection> &shapes, Mat &img);



int main(int argc, char **argv)
{
    //unsigned double start = time(0);
    if (argc == 1)
    {
        cout << "Call this program like this:" << endl;
        cout << "Linux: ./face_detection num_of_frames faces.1.png" << endl;
        cout << "Windows: face_detection.exe num_of_frames faces.1.png" << endl;
        cout << "\nYou can get the shape_predictor_68_face_landmarks.dat file from:\n";
        cout << "http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        return 0;
    }

    unsigned int num_of_frames = stoi(argv[1]);
    string first_frame = argv[2];
    //generate all the imgs' file name according to the naming scheme
    std::vector<string> file_names;
    string folder = imgs_name(file_names, num_of_frames, first_frame);

    //load all images into a vector
    std::vector<Mat> imgs = load_img(file_names);

#if defined _MSC_VER
    _mkdir(folder.c_str());
#elif defind __GNUC__
    mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    run(file_names, imgs, "shape_predictor_68_face_landmarks.dat", folder);

    //cout << "time used: " << time(0) - start << endl;
    return 0;
}

string imgs_name(std::vector<string> &names, unsigned int num_frames, string first_frame)
{
    names.push_back(first_frame);

    string subfix = "";
    stringstream prefix;
    bool is_first = true;

    for (int i = first_frame.size() - 1; i >= 0; i--)
    {
        if (first_frame[i] != '.' && is_first == true)
        {
            subfix = first_frame[i] + subfix;
        }
        else if (first_frame[i] == '.' && is_first == true)
        {
            subfix = first_frame[i] + subfix;
            is_first = false;
        }
        else if (first_frame[i] == '.' && is_first == false)
        {
            for (int j = 0; j < i; j++)
            {
                prefix.put(first_frame[j]);
            }
            break;
        }
    }

    string pre = "";
    prefix >> pre;

    for (unsigned int i = 2; i <= num_frames; i++)
    {
        names.push_back(pre + "." + to_string(i) + subfix);
    }

    return "out_" + get_image_name(pre);
}

std::vector<Mat> load_img(const std::vector<string> &names)
{
    std::vector<Mat> imgs;
    for (int i = 0; i < names.size(); i++)
    {
        Mat img = imread(names[i]);
        if (img.empty())
        {
            cout << "Could not open or find image " << names[i] << endl;
            continue;
        }
        imgs.push_back(img);
    }
    return imgs;
}

string get_image_name(string name)
{
    string image_name = "";
    for (int i = name.size() - 1; i >= 0; i--)
    {
        if (name[i] != '/' && name[i] != '\\')
        {
            image_name = name[i] + image_name;
        }
        else
        {
            return image_name;
        }
    }
    cout << image_name << endl;
    return image_name;
}

void run(std::vector<string> &imgs_name, std::vector<Mat> &imgs, char *predictor, const string folder)
{
    time_t start = time(0);

    frontal_face_detector detector = get_frontal_face_detector();
    shape_predictor sp;
    deserialize(predictor) >> sp;

    for (unsigned int i = 0; i < imgs_name.size(); i++)
    {
        //array2d<rgb_pixel> img;
        //load_image(img, imgs_name[i]);
        /*
        Mat img = imread(imgs_name[i]);
        if (img.empty())
        {
            cout << "Could not open or find image " << imgs_name[i] << endl;
            return;
        }
        */
        cv_image<bgr_pixel> cimg(imgs[i]);

        std::vector<dlib::rectangle> dets = detector(cimg);     //faces

        std::vector<full_object_detection> shapes;
        for (unsigned int j = 0; j < dets.size(); j++)
        {
            full_object_detection shape = sp(cimg, dets[j]);
            shapes.push_back(shape);
        }

        std::vector<cv::Rect> cv_faces;
        for (int k = 0; k < dets.size(); k++)
        {
            cv_faces.push_back(dlib_rect_to_opencv_rect(dets[k]));
        }
        std::vector<Dual_Points> eyes = eye_detection(imgs[i], cv_faces);
        std::vector<Dual_Points> heads = head_pose_estimation(shapes, imgs[i]);

        draw_delaunay_triangles(shapes, imgs[i]);
        draw_eye_center(imgs[i], eyes);
        draw_head_posting(imgs[i], heads);

        string image_name = get_image_name(imgs_name[i]);
        imwrite("./" + folder + "/out_" + image_name, imgs[i]);
        //cout << "./" + folder + "/out_" + image_name << endl;
        cout << "\nframe#: " << i << endl;
        cout << "time used: " << time(0) - start << endl;
    }
}

cv::Rect dlib_rect_to_opencv_rect(const dlib::rectangle &rect)
{
    return cv::Rect(cv::Point2i(rect.left(), rect.top()), cv::Point2i(rect.right() + 1, rect.bottom() + 1));
}

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

void draw_eye_center(Mat &img, const std::vector<Dual_Points> &p)
{
    for (int i = 0; i < p.size(); i++)
    {
        cv::circle(img, p[i].point1, 3, cv::Scalar(255, 255, 255));
        cv::circle(img, p[i].point2, 3, cv::Scalar(255, 255, 255));
    }
}

void draw_head_posting(Mat &img, const std::vector<Dual_Points> &p)
{
    for (int i = 0; i < p.size(); i++)
    {
        cv::line(img, p[i].point1, p[i].point2, cv::Scalar(0, 255, 0), 2);
    }
}
