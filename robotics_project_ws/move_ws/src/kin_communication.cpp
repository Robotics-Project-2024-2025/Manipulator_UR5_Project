//
//  kin_communication.cpp
//  Kinematics
//
//  Created by Matteo Gottardelli on 04/12/24.
//

#include "kin_communication.h"

TrajectoryPublisher::TrajectoryPublisher(MatrixD6 Th) : Node("trajectory_publisher")
{
    // Create a publisher for the scaled joint trajectory controller
    trajectory_publisher_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>(
        "/scaled_joint_trajectory_controller/joint_trajectory", 10);

    // Create a timer that will periodically publish a trajectory
    timer_ = this->create_wall_timer(
                                     1s, [this, Th]() {this->publish_iter(Th);});
}
void TrajectoryPublisher::publish_iter(MatrixD6 Th)
{
    trajectory_msgs::msg::JointTrajectory traj_msg;
    init_Trajectory(&traj_msg);
    naming_Points(&traj_msg);
    for (int j=0; j<NUM_JOINTS; j++) {
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
void TrajectoryPublisher::init_Trajectory(trajectory_msgs::msg::JointTrajectory* traj_msg) {
    traj_msg->header.stamp=this->now();
    traj_msg->header.frame_id = "base_link";
    
}
string TrajectoryPublisher::chooseName(int index) {
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
void TrajectoryPublisher::naming_Points(trajectory_msgs::msg::JointTrajectory* traj_msg){
    for (int i=0; i<NUM_JOINTS; i++) {
        traj_msg->joint_names.push_back(chooseName(i));
    }
}
void TrajectoryPublisher::add_point(trajectory_msgs::msg::JointTrajectory* traj_msg, trajectory_msgs::msg::JointTrajectoryPoint p) {
    traj_msg->points.push_back(p);
}
void TrajectoryPublisher::publish_trajectory(trajectory_msgs::msg::JointTrajectory traj_msg) {
    // Publish the trajectory
    trajectory_publisher_->publish(traj_msg);
    RCLCPP_INFO(this->get_logger(), "Published trajectory with %zu points", traj_msg.points.size());
}
void send_trajectory(MatrixD6 th) {
    cout << "Sending trajectory..." << endl;
    rclcpp::spin(std::make_shared<TrajectoryPublisher>(th));
    rclcpp::shutdown();
    cout << "End Sending trajectory" << endl;
}
void setupCommunication(int argc, const char* argv[]) {
    cout << "Communications Setup Start" << endl;
    rclcpp::init(argc, argv);
    cout << "Communications Setup Complete" << endl;
}
