#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include "eyeLike.h"
#include "constants.h"
#include "findEyeCenter.h"

using namespace std;
using namespace cv;
using namespace dlib;


/** Constants **/


/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
/*
cv::String face_cascade_name = "../res/haarcascade_frontalface_alt.xml";
cv::CascadeClassifier face_cascade;
std::string main_window_name = "Capture - Face detection";
std::string face_window_name = "Capture - Face";
cv::RNG rng(12345);
cv::Mat debugImage;
cv::Mat skinCrCbHist = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);
*/

Dual_Points findEyes(cv::Mat frame_gray, std::pair<cv::Rect, cv::Rect> &eye_regions)
{
    //cv::Mat faceROI = frame_gray(face);
    //cv::Mat debugFace = faceROI;

    //if (kSmoothFaceImage)
    //{
    //    double sigma = kSmoothFaceFactor * face.width;
    //    GaussianBlur(faceROI, faceROI, cv::Size(0, 0), sigma);
    //}
    //-- Find eye regions and draw them
    /*
    int eye_region_width = face.width * (kEyePercentWidth / 100.0);
    int eye_region_height = face.width * (kEyePercentHeight / 100.0);
    int eye_region_top = face.height * (kEyePercentTop / 100.0);
    cv::Rect leftEyeRegion(face.width * (kEyePercentSide / 100.0),
                            eye_region_top, eye_region_width, eye_region_height);
    cv::Rect rightEyeRegion(face.width - eye_region_width - face.width * (kEyePercentSide / 100.0),
                            eye_region_top, eye_region_width, eye_region_height);
    */
    cv::Rect leftEyeRegion = eye_regions.first;
    cv::Rect rightEyeRegion = eye_regions.second;

    //-- Find Eye Centers
    cv::Point leftPupil = findEyeCenter(frame_gray, leftEyeRegion);
    cv::Point rightPupil = findEyeCenter(frame_gray, rightEyeRegion);
    /*
    // get corner regions
    cv::Rect leftRightCornerRegion(leftEyeRegion);
    leftRightCornerRegion.width -= leftPupil.x;
    leftRightCornerRegion.x += leftPupil.x;
    leftRightCornerRegion.height /= 2;
    leftRightCornerRegion.y += leftRightCornerRegion.height / 2;
    cv::Rect leftLeftCornerRegion(leftEyeRegion);
    leftLeftCornerRegion.width = leftPupil.x;
    leftLeftCornerRegion.height /= 2;
    leftLeftCornerRegion.y += leftLeftCornerRegion.height / 2;
    cv::Rect rightLeftCornerRegion(rightEyeRegion);
    rightLeftCornerRegion.width = rightPupil.x;
    rightLeftCornerRegion.height /= 2;
    rightLeftCornerRegion.y += rightLeftCornerRegion.height / 2;
    cv::Rect rightRightCornerRegion(rightEyeRegion);
    rightRightCornerRegion.width -= rightPupil.x;
    rightRightCornerRegion.x += rightPupil.x;
    rightRightCornerRegion.height /= 2;
    rightRightCornerRegion.y += rightRightCornerRegion.height / 2;
     */
/*
    rectangle(debugFace, leftRightCornerRegion, 200);
    rectangle(debugFace, leftLeftCornerRegion, 200);
    rectangle(debugFace, rightLeftCornerRegion, 200);
    rectangle(debugFace, rightRightCornerRegion, 200);
*/
    // change eye centers to face coordinates
    rightPupil.x += rightEyeRegion.x;
    rightPupil.y += rightEyeRegion.y;
    leftPupil.x += leftEyeRegion.x;
    leftPupil.y += leftEyeRegion.y;
    // draw eye centers
/*
    circle(debugFace, rightPupil, 3, 1234);
    circle(debugFace, leftPupil, 3, 1234);
*/
/*
    rightPupil.x += face.x;
    rightPupil.y += face.y;
    leftPupil.x += face.x;
    leftPupil.y += face.y;
*/

    //circle(source_img, leftPupil, 3, cv::Scalar(255, 255, 255));
    //circle(source_img, rightPupil, 3, cv::Scalar(255, 255, 255));
    Dual_Points p;
    p.point1 = leftPupil;
    p.point2 = rightPupil;
    return p;
}


std::vector<Dual_Points> eye_detection(cv::Mat &frame,
                                       const std::vector<cv::Rect> &faces,
                                       std::vector<std::pair<cv::Rect, cv::Rect>> &eyes_regions)
{
    std::vector<cv::Mat> rgbChannels(3);
    cv::split(frame, rgbChannels);
    cv::Mat frame_gray = rgbChannels[2];

    std::vector<Dual_Points> p;

    for (int i = 0; i < faces.size(); i++)
    {
        p.push_back(findEyes(frame_gray, eyes_regions[i]));
    }
    return p;
}

// draw small circle on eye pupils
void draw_eye_center(cv::Mat &img, const std::vector<Dual_Points> &p)
{
    for (int i = 0; i < p.size(); i++)
    {
        cv::circle(img, p[i].point1, 3, cv::Scalar(255, 255, 255));
        cv::circle(img, p[i].point2, 3, cv::Scalar(255, 255, 255));
    }
}

// return: Dual_Points -- left eye and right eye's location for each face in an image
// find eye pupils
// get the eye's region by using 68 face landmarks
std::vector<Dual_Points> eye_pupils(
        cv::Mat &image,
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
