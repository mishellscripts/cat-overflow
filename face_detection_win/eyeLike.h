#ifndef FACE_DETECTION_EYELIKE_H
#define FACE_DETECTION_EYELIKE_H

#include "constants.h"

Dual_Points findEyes(cv::Mat frame_gray, cv::Rect face, std::pair<cv::Rect, cv::Rect> &eye_regions);

//cv::Mat findSkin(cv::Mat &frame);
std::vector<Dual_Points> eye_detection(cv::Mat &frame,
                                       const std::vector<cv::Rect> &faces,
                                       std::vector<std::pair<cv::Rect, cv::Rect>> &eyes_regions);

// draw small circle on eye pupils
void draw_eye_center(cv::Mat &img, const std::vector<Dual_Points> &p, const std::vector<dlib::full_object_detection> &shapes);

// return: Dual_Points -- left eye and right eye's location for each face in an image
// find eye pupils
// get the eye's region by using 68 face landmarks
std::vector<Dual_Points> eye_pupils(
        cv::Mat &image,
        const std::vector<cv::Rect> &faces,
        const std::vector<dlib::full_object_detection> &shapes);

#endif //FACE_DETECTION_EYELIKE_H
