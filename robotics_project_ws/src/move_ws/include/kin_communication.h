//
//  kin_communication.h
//  Kinematics
//
//  Created by Matteo Gottardelli on 28/11/24.
//

#ifndef kin_communication_h
#define kin_communication_h
#include "kinematics.h"
#include <rclcpp/rclcpp.hpp>
#include <control_msgs/action/follow_joint_trajectory.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <chrono>
#include <iostream>
#include <Eigen/Dense>

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
using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
using GoalHandleFollowJointTrajectory = rclcpp_action::ClientGoalHandle<FollowJointTrajectory>;
class TrajectoryActionClient : public rclcpp::Node
{
public:
    TrajectoryActionClient(MatrixD6 Th, std::shared_ptr<rclcpp::Node> node);
private:
    rclcpp_action::Client<FollowJointTrajectory>::SharedPtr action_client_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<rclcpp::Node> origin_node;
    void publish_iter(MatrixD6 Th);
    void init_Trajectory(trajectory_msgs::msg::JointTrajectory* traj_msg);
    string chooseName(int index);
    void naming_Points(trajectory_msgs::msg::JointTrajectory* traj_msg);
    void add_point(trajectory_msgs::msg::JointTrajectory* traj_msg, trajectory_msgs::msg::JointTrajectoryPoint p);
    void publish_trajectory(trajectory_msgs::msg::JointTrajectory traj_msg);
    void handle_trajectory_success();
    trajectory_msgs::msg::JointTrajectory traj_msg;
};

class JointReceiver : public rclcpp::Node
{
public:
    JointReceiver();
    shared_ptr<const
    sensor_msgs::msg::JointState>get_joint_state() const;
private:
    rclcpp::Subscription< sensor_msgs::msg::JointState>::SharedPtr joint_receiver_;
    shared_ptr<const sensor_msgs::msg::JointState> joint_state_;
};
Matrix16 receive_joint_state();
void send_trajectory(MatrixD6 th, std::shared_ptr<rclcpp::Node> node);
void setupCommunication(int argc, const char* argv[]);
#endif /* kin_communication_h */
