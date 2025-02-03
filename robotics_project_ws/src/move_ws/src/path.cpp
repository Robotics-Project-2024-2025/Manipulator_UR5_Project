//
//  path.cpp
//  Robotics
//
//  Created by Niccol� Cristoforetti on 05/12/24.
//

#include "path.h"
using namespace std;


MyVector::MyVector() : Node("path_acquiring") {
    service_=this->create_service<MoveService>("service_path", bind(&MyVector::calculatePath, this, std::placeholders::_1, std::placeholders::_2));
    auto shared_this=shared_ptr<MyVector>(this);
    while(1) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to take path vectors xe1(x,y,z) phie1(x,y,z)");
        //rclcpp::spin_some(shared_this);
        rclcpp::spin(shared_this);
        this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void MyVector::calculatePath(
    const shared_ptr<MoveService::Request> request,
    shared_ptr<MoveService::Response> response){
    //cout << qES << endl;
    MatrixD6 th;
    std::shared_ptr<rclcpp::Node> node;
    Vector3d v, p;
    v << request->xe1.x, request->xe1.y, request->xe1.z;
    p << request->phie1.x, request->phie1.y, request->phie1.z;
    Matrix16 qES;
    for (int i=0; i<NUM_JOINTS; i++) {
        qES(i)=request->joints[i];
    }
    RCLCPP_INFO(this->get_logger(), "Checking Position");
   /* if (!checkPosition(v, qES)) {
        RCLCPP_ERROR(this->get_logger(), "Target position is unreachable");
        response->result = false;
        return;
    }*/

    if (!p2pMotionPlan(qES, v, p, MINT, MAXT, &th, true, DEFAULT, 0.0)) {
        RCLCPP_ERROR(this->get_logger(), "Error in trajectory computation");
        response->result = false;
        return;
    }
    RCLCPP_INFO(this->get_logger(), "Trajectory planning successful, sending trajectory");
    std::mutex mtx;
    std::condition_variable cv;
    bool action_completed = false;
    bool action_result = false;
    int retries=0;
    int max_retries=0;
    auto traj_node=std::make_shared<TrajectoryActionClient>(th, node);
    // Prepare goal
    auto goal_msg = FollowJointTrajectory::Goal();
    //goal_msg.trajectory = traj_node->get_trajectory(); // Convert your trajectory to ROS msg

    // Prepare action client options
    auto send_goal_options = rclcpp_action::Client<FollowJointTrajectory>::SendGoalOptions();
    //auto action_client_=traj_node->get_action_client();
    send_goal_options.goal_response_callback =
    [this, &retries, max_retries, &action_result, &goal_msg, &action_completed, &send_goal_options, &cv, &mtx](const GoalHandleFollowJointTrajectory::SharedPtr& goal_handle) {
    if (!goal_handle) {
    RCLCPP_ERROR(this->get_logger(), "Goal was rejected by the server");

    // Retry logic
        if (retries < max_retries) {
           retries++;
           RCLCPP_INFO(this->get_logger(), "Retrying goal submission... Attempt %d of %d", retries, max_retries);
           // Retry sending the goal after a delay
           std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay before retry
           //action_client_->async_send_goal(goal_msg, send_goal_options); // Resend goal
        } else {
           RCLCPP_ERROR(this->get_logger(), "Max retries reached. Not retrying further.");
           action_completed = true; // End the action after max retries
           action_result = false;
           cv.notify_one(); // Notify to exit waiting
        }
    } else {
        RCLCPP_INFO(this->get_logger(), "Goal accepted by the server");
    }
    };

    send_goal_options.result_callback =
        [&action_completed, &action_result, &cv, &mtx, this](const GoalHandleFollowJointTrajectory::WrappedResult& result) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                action_completed = true;

                if (result.code == rclcpp_action::ResultCode::SUCCEEDED) {
                    RCLCPP_INFO(this->get_logger(), "Goal succeeded");
                    action_result = true;
                } else {
                    //RCLCPP_ERROR(this->get_logger(), "Goal failed with code: %d", result.code);
                    action_result = false;
                }
            }
            cv.notify_one();
        };

    // Send the goal asynchronously
    /*if (!action_client_->wait_for_action_server()) {
        RCLCPP_ERROR(this->get_logger(), "Action server not available!");
        response->result = false;
        return;
    }*/
    //action_client_->async_send_goal(goal_msg, send_goal_options);
    RCLCPP_INFO(this->get_logger(), "Trajectory Sent");
    std::thread spin_thread([traj_node]() {
            rclcpp::executors::SingleThreadedExecutor executor;
            executor.add_node(traj_node);
            executor.spin();
            executor.remove_node(traj_node);
        });
    // Wait for the action to complete
    {
        std::unique_lock<std::mutex> lock(mtx);
        RCLCPP_INFO(this->get_logger(), "In Mutex");
        cv.wait(lock, [&action_completed] { return action_completed; });
    }
    spin_thread.detach();
    RCLCPP_INFO(this->get_logger(), "Out Mutex");
    if (action_result) {
        RCLCPP_INFO(this->get_logger(), "Trajectory execution successful");
        response->result =true;
    } else {
        RCLCPP_ERROR(this->get_logger(), "Trajectory execution failed");
        response->result =false;
    }
}
bool path(Vector3d xe1, Vector3d phie1, Matrix61 joint_states, std::shared_ptr<rclcpp::Node> node){
    MatrixD6 th;
    RCLCPP_INFO(node->get_logger(), "Checking Position");
    //if(checkPosition(xe1, joint_states)) {
        if(p2pMotionPlan(joint_states, xe1, phie1, MINT, MAXT, &th, true, DEFAULT, 0.0)) {
            RCLCPP_INFO(node->get_logger(), "Moving to HOME");
            send_trajectory(th, node);
        }
        else {
            RCLCPP_INFO(node->get_logger(), "Error in computation of trajectory to point ");
            return false;
        }
   /* }
    else {
        RCLCPP_INFO(node->get_logger(), "Impossible to Reach the final Position ");
        return false;
    }*/
    return true;
}

int main (int argc, const char* argv[]) {
    rclcpp::init(argc, argv);
    while (1) {
        auto node=make_shared<MyVector>();
    }
    rclcpp::shutdown();
    return 0;
}

