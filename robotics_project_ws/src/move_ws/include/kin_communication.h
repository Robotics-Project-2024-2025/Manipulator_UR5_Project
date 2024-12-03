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
    TrajectoryPublisher(MatrixD6 Th) : Node("trajectory_publisher")
    {
        // Create a publisher for the scaled joint trajectory controller
        trajectory_publisher_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>(
            "/scaled_joint_trajectory_controller/joint_trajectory", 10);

        // Create a timer that will periodically publish a trajectory
        timer_ = this->create_wall_timer(
                                         1s, [this, Th]() {this->publish_iter(Th);});
    }

private:
    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr trajectory_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    void publish_iter(MatrixD6 Th)
    {
        trajectory_msgs::msg::JointTrajectory traj_msg;
        init_Trajectory(&traj_msg);
        naming_Points(&traj_msg);
        for (int j=0; j<6; j++) {
            trajectory_msgs::msg::JointTrajectoryPoint point;
            point.time_from_start=rclcpp::Duration(2.0s);
            for (int i=0; i<Th.rows(); i++) {
                point.positions.push_back(Th(i, j));
                point.velocities.push_back(0.0);
                point.accelerations.push_back(0.0);
                point.effort.push_back(0.0);
                add_point(&traj_msg, point);
                cout << i*100+j << endl;
            }
        }
        publish_trajectory(traj_msg);
    }
    void init_Trajectory(trajectory_msgs::msg::JointTrajectory* traj_msg) {
        traj_msg->header.stamp=this->now();
        traj_msg->header.frame_id = "base_link";
        
    }
    string chooseName(int index) {
        string tmp;
        switch(index) {
            case 0: tmp=SHOULDER_PAN; break;
            case 1: tmp=SHOULDER_LIFT; break;
            case 2: tmp=ELBOW; break;
            case 3: tmp=WRIST_1; break;
            case 4: tmp=WRIST_2; break;
            case 5: tmp=WRIST_3; break;
            default: exit(1);
        }
        return tmp;
    }
    void naming_Points(trajectory_msgs::msg::JointTrajectory* traj_msg) {
        for (int i=0; i<NUM_JOINTS; i++) {
            traj_msg->joint_names.push_back(chooseName(i));
        }
    }
    void add_point(trajectory_msgs::msg::JointTrajectory* traj_msg, trajectory_msgs::msg::JointTrajectoryPoint p) {
        traj_msg->points.push_back(p);
    }
    void publish_trajectory(trajectory_msgs::msg::JointTrajectory traj_msg) {
        // Publish the trajectory
        trajectory_publisher_->publish(traj_msg);
        RCLCPP_INFO(this->get_logger(), "Published trajectory with %zu points", traj_msg.points.size());
    }
};

#endif /* kin_communication_h */
