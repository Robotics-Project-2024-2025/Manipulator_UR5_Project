//
//  kin_communication.h
//  Kinematics
//
//  Created by Matteo Gottardelli on 28/11/24.
//

#ifndef kin_communication_h
#define kin_communication_h
#include <rclcpp/rclcpp.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <trajectory_msgs/msg/joint_trajectory_point.hpp>
#include <std_msgs/msg/header.hpp>
#include <iostream>
#include <Eigen/Dense>
#include <chrono>
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
using namespace std;
using namespace Eigen;
using MatrixD6=Matrix<double, -1, 6>;

using namespace std::chrono_literals;

class TrajectoryPublisher : public rclcpp::Node
{
public:
    TrajectoryPublisher() : Node("trajectory_publisher")
    {
         increment_ = 0.0;  // Initialize the increment
        // Create a publisher for the scaled joint trajectory controller
        trajectory_publisher_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>(
            "/scaled_joint_trajectory_controller/joint_trajectory", 10);

        // Create a timer that will periodically publish a trajectory
        timer_ = this->create_wall_timer(
            1s, std::bind(&TrajectoryPublisher::publish_trajectory, this));
    }

private:
    void publish_trajectory()
    {
        // Create the JointTrajectory message
        trajectory_msgs::msg::JointTrajectory traj_msg;
        traj_msg.header.stamp = this->now();  // Set the current timestamp
        traj_msg.header.frame_id = "base_link";  // Set the appropriate reference frame

        // Define the joint names for the trajectory
        traj_msg.joint_names = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint", "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};

        // Create a joint trajectory point
        trajectory_msgs::msg::JointTrajectoryPoint point;
        point.positions = {0.17 + increment_, -1.41, 1.84, -0.43, 0.17, -0.38};  // Example positions for each joint
        point.velocities = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};  // Zero velocities
        point.accelerations = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};  // Zero accelerations

        increment_ += 0.1;  // Increment the position for the next trajectory

        // Set the time from the start for each point (e.g., 2 seconds)
        point.time_from_start = rclcpp::Duration(2.0s);

        // Add the point to the trajectory message
        traj_msg.points.push_back(point);

        // Publish the trajectory
        trajectory_publisher_->publish(traj_msg);
        RCLCPP_INFO(this->get_logger(), "Published trajectory with %zu points", traj_msg.points.size());
    }

    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr trajectory_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    double increment_;
};

#endif /* kin_communication_h */
