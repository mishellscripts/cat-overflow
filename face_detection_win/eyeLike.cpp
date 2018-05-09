#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "eyeLike.h"
#include "constants.h"
#include "findEyeCenter.h"

using namespace std;
using namespace cv;
using namespace dlib;

#define PI 3.14159265



Dual_Points findEyes(cv::Mat frame_gray, std::pair<cv::Rect, cv::Rect> &eye_regions)
{
    cv::Rect leftEyeRegion = eye_regions.first;
    cv::Rect rightEyeRegion = eye_regions.second;

    //-- Find Eye Centers
    cv::Point leftPupil = findEyeCenter(frame_gray, leftEyeRegion);
    cv::Point rightPupil = findEyeCenter(frame_gray, rightEyeRegion);

    // change eye centers to face coordinates
    rightPupil.x += rightEyeRegion.x;
    rightPupil.y += rightEyeRegion.y;
    leftPupil.x += leftEyeRegion.x;
    leftPupil.y += leftEyeRegion.y;

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
void draw_eye_center(cv::Mat &img, const std::vector<Dual_Points> &p, const std::vector<full_object_detection> &shapes)
{
    for (int i = 0; i < p.size(); i++)
    {
        cv::circle(img, p[i].point1, 3, cv::Scalar(255, 255, 255));
        cv::circle(img, p[i].point2, 3, cv::Scalar(255, 255, 255));

        int mouthX = shapes[i].part(9).x();
        int mouthY = shapes[i].part(9).y();
        int length = abs(p[i].point2.y - mouthY) * 0.6;

        int leftEarX =  mouthX - 2 * abs(p[i].point1.x - mouthX);
        int rightEarX = mouthX + 2 * abs(p[i].point2.x - mouthX);
        int leftEarY =  mouthY - 2 * abs(p[i].point1.y - mouthY);
        int rightEarY = mouthY - 2 * abs(p[i].point2.y - mouthY);

        double lAngle = atan(1.0 * abs(p[i].point1.x - mouthX) / abs(p[i].point1.y - mouthY));
        int left1dx = length * sin(lAngle  - 15 * PI / 180);
        int left1dy = length * cos(lAngle  - 15 * PI / 180);
        int left2dx = length * sin(lAngle  + 15 * PI / 180);
        int left2dy = length * cos(lAngle  + 15 * PI / 180);

        double rAngle = atan(1.0 * abs(p[i].point2.x - mouthX) / abs(p[i].point2.y - mouthY));
        int right1dx = length * sin(rAngle  - 15 * PI / 180);
        int right1dy = length * cos(rAngle  - 15 * PI / 180);
        int right2dx = length * sin(rAngle  + 15 * PI / 180);
        int right2dy = length * cos(rAngle  + 15 * PI / 180);

        int wlength = abs(p[i].point2.y - mouthY) * 0.1;

        int thickness = 5;
        cv::Scalar color = cv::Scalar(255, 255, 0);

        // draw ears
        cv::line(img, cv::Point2i(leftEarX + left1dx, leftEarY + left1dy), cv::Point2i(leftEarX, leftEarY), color, thickness);
        cv::line(img, cv::Point2i(leftEarX + left2dx, leftEarY + left2dy), cv::Point2i(leftEarX, leftEarY), color, thickness);
        cv::line(img, cv::Point2i(rightEarX - right1dx, rightEarY + right1dy), cv::Point2i(rightEarX, leftEarY), color, thickness);
        cv::line(img, cv::Point2i(rightEarX - right2dx, rightEarY + right2dy), cv::Point2i(rightEarX, leftEarY), color, thickness);

        //draw whiskers
        cv::line(img, cv::Point2i(shapes[i].part(48).x() - 0.5 * wlength, shapes[i].part(48).y() - wlength), cv::Point2i(shapes[i].part(2).x(), shapes[i].part(2).y()), color, thickness);
        cv::line(img, cv::Point2i(shapes[i].part(48).x() - 0.5 * wlength, shapes[i].part(48).y()), cv::Point2i(shapes[i].part(3).x(), shapes[i].part(3).y()), color, thickness);
        cv::line(img, cv::Point2i(shapes[i].part(48).x() - 0.5 * wlength, shapes[i].part(48).y() + wlength), cv::Point2i(shapes[i].part(4).x(), shapes[i].part(4).y()), color, thickness);

        cv::line(img, cv::Point2i(shapes[i].part(54).x() + 0.5 * wlength, shapes[i].part(54).y() - wlength), cv::Point2i(shapes[i].part(14).x(), shapes[i].part(14).y()), color, thickness);
        cv::line(img, cv::Point2i(shapes[i].part(54).x() + 0.5 * wlength, shapes[i].part(54).y()), cv::Point2i(shapes[i].part(13).x(), shapes[i].part(13).y()), color, thickness);
        cv::line(img, cv::Point2i(shapes[i].part(54).x() + 0.5 * wlength, shapes[i].part(54).y() + wlength), cv::Point2i(shapes[i].part(12).x(), shapes[i].part(12).y()), color, thickness);

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
