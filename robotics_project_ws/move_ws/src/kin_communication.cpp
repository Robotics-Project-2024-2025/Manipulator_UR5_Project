//
//  kin_communication.cpp
//  Kinematics
//
//  Created by Matteo Gottardelli on 04/12/24.
//

#include "kin_communication.h"
using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
using GoalHandleFollowJointTrajectory = rclcpp_action::ClientGoalHandle<FollowJointTrajectory>;

TrajectoryActionClient::TrajectoryActionClient(MatrixD6 Th) : Node("trajectory_publisher")
{
    // Create a publisher for the scaled joint trajectory controller
    //action_client_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>("/scaled_joint_trajectory_controller/joint_trajectory", 10);
    action_client_ = rclcpp_action::create_client<FollowJointTrajectory>(
        this, "/scaled_joint_trajectory_controller/follow_joint_trajectory");
    // Wait for the action server to be available
    if (!action_client_->wait_for_action_server(10s))
    {
        RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
        rclcpp::shutdown();
    }
    publish_iter(Th);
}
void TrajectoryActionClient::publish_iter(MatrixD6 Th)
{
    trajectory_msgs::msg::JointTrajectory traj_msg;
    init_Trajectory(&traj_msg);
    naming_Points(&traj_msg);
    for (int i=0; i<Th.rows(); i++) {
        trajectory_msgs::msg::JointTrajectoryPoint point;
        point.time_from_start=rclcpp::Duration(2.0s);
        for (int j=0; j<NUM_JOINTS; j++) {
            point.positions.push_back(Th(i, j));
            point.velocities.push_back(0.0);
            point.accelerations.push_back(0.0);
            //point.effort.push_back(0.0);
            point.time_from_start=rclcpp::Duration(2.0s+i*0.01s);
        }
        add_point(&traj_msg, point);
    }
    publish_trajectory(traj_msg);
}
void TrajectoryActionClient::init_Trajectory(trajectory_msgs::msg::JointTrajectory* traj_msg) {
    traj_msg->header.stamp=this->now();
    traj_msg->header.frame_id = "base_link";
    
}
string TrajectoryActionClient::chooseName(int index) {
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
void TrajectoryActionClient::naming_Points(trajectory_msgs::msg::JointTrajectory* traj_msg){
    for (int i=0; i<NUM_JOINTS; i++) {
        traj_msg->joint_names.push_back(chooseName(i));
     }
}
void TrajectoryActionClient::add_point(trajectory_msgs::msg::JointTrajectory* traj_msg, trajectory_msgs::msg::JointTrajectoryPoint p) {
    traj_msg->points.push_back(p);
}
void TrajectoryActionClient::publish_trajectory(trajectory_msgs::msg::JointTrajectory traj_msg) {
    // Create a goal message for the action
    auto goal_msg = FollowJointTrajectory::Goal();
    goal_msg.trajectory = traj_msg;

    RCLCPP_INFO(this->get_logger(), "Sending trajectory goal");

    // Send the goal to the action server
    auto send_goal_options = rclcpp_action::Client<FollowJointTrajectory>::SendGoalOptions();
    send_goal_options.goal_response_callback =
        [this](const GoalHandleFollowJointTrajectory::SharedPtr& goal_handle) {
            if (!goal_handle)
            {
                RCLCPP_ERROR(this->get_logger(), "Goal was rejected by the server");
            }
            else
            {
                RCLCPP_INFO(this->get_logger(), "Goal accepted by the server, waiting for result");
            }
        };

    send_goal_options.result_callback =
        [this](const GoalHandleFollowJointTrajectory::WrappedResult &result) {
            switch (result.code)
            {
            case rclcpp_action::ResultCode::SUCCEEDED:
                RCLCPP_INFO(this->get_logger(), "Goal succeeded");
                break;
            case rclcpp_action::ResultCode::ABORTED:
                RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
                break;
            case rclcpp_action::ResultCode::CANCELED:
                RCLCPP_WARN(this->get_logger(), "Goal was canceled");
                break;
            default:
                RCLCPP_ERROR(this->get_logger(), "Unknown result code");
                break;
            }
        };
        action_client_->async_send_goal(goal_msg, send_goal_options);

}

JointReceiver::JointReceiver() : Node("arm_receiver") {
        joint_receiver_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "/joint_states", 10, [this](std::shared_ptr<sensor_msgs::msg::JointState> msg) {
                joint_state_ = const_pointer_cast<const sensor_msgs::msg::JointState>(msg);
                RCLCPP_INFO(this->get_logger(), "Received Joint State message");
                cout << "Received Joint State message" << endl;
            });
    while (rclcpp::ok() && !joint_state_) {
        rclcpp::spin_some(this->get_node_base_interface());
    }
    if(joint_state_) {
        RCLCPP_INFO(this->get_logger(), "Successfully Received Joint State");
        cout << "Successfully Received Joint State" << endl;
    }
}

shared_ptr<const sensor_msgs::msg::JointState> JointReceiver::get_joint_state() const {
    return joint_state_;
}

void send_trajectory(MatrixD6 th) {
    cout << "Sending trajectory..." << endl;
    rclcpp::spin(std::make_shared<TrajectoryActionClient>(th));
    rclcpp::shutdown();
    cout << "End Sending trajectory" << endl;
}

void setupCommunication(int argc, const char* argv[]) {
    cout << "Communications Setup Start" << endl;
    rclcpp::init(argc, argv);
    cout << "Communications Setup Complete" << endl;
}
Matrix16 receive_joint_state() {
    cout << "Requesting Actual Joint States" << endl;
    auto node= std::make_shared<JointReceiver>();
    auto joint_result=node->get_joint_state();
    Matrix16 ret;
    if (joint_result!=NULL) {
        for (int i=0; i<NUM_JOINTS; i++) {
            RCLCPP_INFO(rclcpp::get_logger("main"), "JointState received:Position[%d]: %f", i,
                        joint_result->position.empty() ? 0.0 :
                            joint_result->position[i]);
            int j=i+1;
            if (j<NUM_JOINTS) {
                ret(j)=joint_result->position[i];
            }
            else {
                ret(0)=joint_result->position[i];
            }
        }
    } else {
        RCLCPP_WARN(rclcpp::get_logger("main"), "No JointState received.");
    }
    rclcpp::shutdown();
    cout << "End Joint State Receiving" << endl;
    return ret;
}
