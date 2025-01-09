//
//  complete_job.h
//  Robotics
//
//  Created by Matteo Gottardelli on 05/01/25.
//

#ifndef __COMPLETE_JOB_H__
#define __COMPLETE_JOB_H__
#include <rclcpp/rclcpp.hpp>
#include <vector>
#include <rclcpp_action/rclcpp_action.hpp>
#include "std_srvs/srv/trigger.hpp"
#include <Eigen/Dense>
#include "kin_communication.h"
#include "kinematics.h"
using namespace std;

extern int position;
bool path(Vector3d xe1, Vector3d phie1, Matrix16 joint_states, std::shared_ptr<rclcpp::Node> node);
void generalizeMovement (std::shared_ptr<rclcpp::Node> node, Vector3d destinationPos, Vector3d destinationOri);
void oneIteration(std::shared_ptr<rclcpp::Node> node);

#endif /* path_h */


