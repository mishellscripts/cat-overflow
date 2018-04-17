#ifndef FACE_DETECTION_EYELIKE_H
#define FACE_DETECTION_EYELIKE_H

#include "constants.h"

Dual_Points findEyes(cv::Mat frame_gray, cv::Mat &source_img, cv::Rect face);
//cv::Mat findSkin(cv::Mat &frame);
std::vector<Dual_Points> eye_detection(cv::Mat &frame,
                                       const std::vector<cv::Rect> &faces,
                                       cv::Rect left_eye,
                                       cv::Rect right_eye);

#endif //FACE_DETECTION_EYELIKE_H
