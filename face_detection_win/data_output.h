//
// Created by POWER on 2018/4/28.
//

#ifndef FACE_DETECTION_DATA_OUTPUT_H
#define FACE_DETECTION_DATA_OUTPUT_H

#include <dlib/image_processing/full_object_detection.h>
#include <opencv2/core/matx.hpp>
#include <nlohmann/json.hpp>
#include "constants.h"

void output_face_landmarks(std::vector<dlib::full_object_detection> shapes,
                           std::vector<Dual_Points> &eyes,
                           cv::Vec3d yaw_pitch_row,
                           nlohmann::json &json);

#endif //FACE_DETECTION_DATA_OUTPUT_H
