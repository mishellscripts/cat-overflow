//
// Created by POWER on 2018/4/22.
//
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>

#include <vector>

#include "delaunay_triangle.h"

using namespace cv;
using namespace dlib;

// draw the blue line triangles onto the image
void draw_delaunay(Mat &img, Subdiv2D &subdiv)
{
    Scalar delaunay_color(255, 0, 0);
    std::vector<Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    std::vector<Point> pt(3);
    Size size = img.size();
    Rect rect(0, 0, size.width, size.height);

    for (int i = 0; i < triangleList.size(); i++)
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
