//
//  kin_communication.h
//  Kinematics
//
//  Created by Matteo Gottardelli on 28/11/24.
//

#ifndef kin_communication_h
#define kin_communication_h
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/init_options.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <trajectory_msgs/msg/joint_trajectory_point.hpp>
#include <std_msgs/msg/header.hpp>
#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <string>
#include <functional>
#include <algorithm>
#include <rcutils/allocator.h>
#include <tracetools/tracetools.h>
#include <memory>

/*
 # The header is used to specify the coordinate frame and the reference time for
 # the trajectory durations
 std_msgs/Header header

 # The names of the active joints in each trajectory point. These names are
 # ordered and must correspond to the values in each trajectory point.
 string[] joint_names

 # Array of trajectory points, which describe the positions, velocities,
 # accelerations and/or efforts of the joints at each time point.
 JointTrajectoryPoint[] points*/

#define SHOULDER_PAN "shoulder_pan_joint"
#define SHOULDER_LIFT "shoulder_lift_joint"
#define ELBOW "elbow_joint"
#define WRIST_1 "wrist_1_joint"
#define WRIST_2 "wrist_2_joint"
#define WRIST_3 "wrist_3_joint"
#define NUM_JOINTS 6
using namespace std;
using namespace Eigen;
using MatrixD6=Matrix<double, -1, 6>;

using namespace std::chrono_literals;

class TrajectoryPublisher : public rclcpp::Node
{
public:
    TrajectoryPublisher(MatrixD6 Th);
private:
    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr trajectory_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    void publish_iter(MatrixD6 Th);
    void init_Trajectory(trajectory_msgs::msg::JointTrajectory* traj_msg);
    string chooseName(int index);
    void naming_Points(trajectory_msgs::msg::JointTrajectory* traj_msg);
    void add_point(trajectory_msgs::msg::JointTrajectory* traj_msg, trajectory_msgs::msg::JointTrajectoryPoint p);
    void publish_trajectory(trajectory_msgs::msg::JointTrajectory traj_msg);
};
/*class JointReceiver : public rclcpp::Node
{
public:
    JointReceiver();
private:
    
};*/
void send_trajectory(MatrixD6 th);
void setupCommunication(int argc, const char* argv[]);
#endif /* kin_communication_h */
