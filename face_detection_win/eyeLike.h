#ifndef FACE_DETECTION_EYELIKE_H
#define FACE_DETECTION_EYELIKE_H

#include "constants.h"

Dual_Points findEyes(cv::Mat frame_gray, cv::Rect face, std::pair<cv::Rect, cv::Rect> &eye_regions);
//cv::Mat findSkin(cv::Mat &frame);
std::vector<Dual_Points> eye_detection(cv::Mat &frame,
                                       const std::vector<cv::Rect> &faces,
                                       std::vector<std::pair<cv::Rect, cv::Rect>> &eyes_regions);

#endif //FACE_DETECTION_EYELIKE_H
