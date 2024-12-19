//
//  path.h
//  Robotics
//
//  Created by Niccol� Cristoforetti on 05/12/24.
//

#ifndef __PATH_H__
#define __PATH_H__
#include <iostream>
#include "kinematics.h" 
#include "kin_communication.h" 
#include <vector>
#include <utility> //check
#include <cmath> //check
#include <Eigen/Dense> 
#include <string>  
//#include <format>
#include <rclcpp/rclcpp.hpp> 
#include "move_ws/msg/vector3d.hpp"
#include "move_ws/srv/moving.hpp"

using namespace std;

bool path(Vector3d xE1, Vector3d phiE1, int argc, const char* argv[]);  

using MoveService=move_ws::srv::Moving;

class MyVector : public rclcpp::Node {
public:
    MyVector();
    void calculatePath(
        const shared_ptr<MoveService::Request> request,
                   shared_ptr<MoveService::Response> response);
private:
    shared_ptr<rclcpp::Service<MoveService>> service_;
};

#endif /* path_h */


