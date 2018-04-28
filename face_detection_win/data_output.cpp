//
// Created by super on 4/18/2018.
//

#include "data_output.h"

using namespace std;
using namespace dlib;

void output_face_landmarks(std::vector<full_object_detection> shapes,
                           std::vector<Dual_Points> &eyes,
                           cv::Vec3d ypr,
                           nlohmann::json &json)
{
    //creates Json object
    //cout << "debug out 23" << endl;
    nlohmann::json json_object;
    for(unsigned int i = 0; i < shapes.size(); i++) {
        //Adds all (x,y) points to json object
        string face = "face_" + to_string(i);
        for (int j = 0; j < 68; j++)
        {
            string point = "point_" + to_string(j);
            json_object[face][point]["x_coord"] = shapes[i].part(j).x();
            json_object[face][point]["y_coord"] = shapes[i].part(j).y();
        }
        json_object[face]["left_eye"]["x_coord"] = eyes[i].point1.x;
        json_object[face]["left_eye"]["y_coord"] = eyes[i].point1.y;

        json_object[face]["right_eye"]["x_coord"] = eyes[i].point2.x;
        json_object[face]["right_eye"]["y_coord"] = eyes[i].point2.y;
        // wait for yaw pitch roll
        json_object[face]["yaw"] = ypr[1];
        json_object[face]["pitch"] = ypr[0];
        json_object[face]["roll"] = ypr[2];
    }
    //cout << "debug out 42" << endl;
    //creates json file and dumps json object
    /*
    std::ofstream json_file;
    json_file.open(file_name + ".json");
    if (json_file.is_open())
    {
        //cout << "debug out 48" << endl;
        json_file << json_object.dump(4) << std::endl;
        json_file.close();
    }
     */
    json = json_object;
}