//
// Created by POWER on 2018/4/22.
//

#ifndef FACE_DETECTION_DELAUNAY_TRIANGLE_H
#define FACE_DETECTION_DELAUNAY_TRIANGLE_H

// draw the blue line triangles onto the image
void draw_delaunay(cv::Mat &img, cv::Subdiv2D &subdiv);

// calculate delaunay triangle by using opencv::Subdiv2D
void draw_delaunay_triangles(std::vector<dlib::full_object_detection> &shapes, cv::Mat &img);

#endif //FACE_DETECTION_DELAUNAY_TRIANGLE_H
