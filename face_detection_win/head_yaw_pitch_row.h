//
// Created by POWER on 2018/4/22.
//

#ifndef FACE_DETECTION_HEAD_YAW_PITCH_ROW_H
#define FACE_DETECTION_HEAD_YAW_PITCH_ROW_H

// calculate head posting
std::vector<Dual_Points> head_pose_estimation(std::vector<dlib::full_object_detection> &shapes,
                                              cv::Mat &img,
                                              cv::Vec3d &yaw_pitch_row);


void get_euler_angles(cv::Mat &rotCamerMatrix, cv::Vec3d &eulerAngles);


// draw a line indicates the head posting
void draw_head_posting(cv::Mat &img, const std::vector<Dual_Points> &p);

#endif //FACE_DETECTION_HEAD_YAW_PITCH_ROW_H
