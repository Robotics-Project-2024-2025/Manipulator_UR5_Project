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

class GripperCommunicator : public rclcpp::Node {
public:
    GripperCommunicator() : Node("gripper_communicator") {
        open_gripper_client_ = this->create_client<std_srvs::srv::Trigger>("open_gripper");
        close_gripper_client_ = this->create_client<std_srvs::srv::Trigger>("close_gripper");
        if (!open_gripper_client_->wait_for_service(std::chrono::seconds(5))) {
            RCLCPP_ERROR(this->get_logger(), "Service open_gripper not available.");
        }
        if (!close_gripper_client_->wait_for_service(std::chrono::seconds(5))) {
                    RCLCPP_ERROR(this->get_logger(), "Service close_gripper not available.");
                }

    }
    void open() {
          callService(open_gripper_client_, "Opening the gripper");
      }

      void close() {
          callService(close_gripper_client_, "Closing the gripper");
      }
private:
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr open_gripper_client_;
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr close_gripper_client_;
    template<typename ServiceClient>
        void callService(ServiceClient client, const std::string &action) {
            RCLCPP_INFO(this->get_logger(), "%s", action.c_str());
            auto request = std::make_shared<std_srvs::srv::Trigger::Request>();
            auto future = client->async_send_request(request);
            if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), future) ==
                rclcpp::FutureReturnCode::SUCCESS) {
                auto response = future.get();
                if (response->success) {
                    RCLCPP_INFO(this->get_logger(), "%s succeeded: %s", action.c_str(), response->message.c_str());
                } else {
                    RCLCPP_WARN(this->get_logger(), "%s failed: %s", action.c_str(), response->message.c_str());
                }
            } else {
                RCLCPP_ERROR(this->get_logger(), "%s service call timed out.", action.c_str());
            }
        }
};

extern int position;
bool path_search(Vector3d xe1, Vector3d phie1, Matrix16 joint_states, std::shared_ptr<rclcpp::Node> node);
void generalizeMovement (std::shared_ptr<rclcpp::Node> node, Vector3d destinationPos, Vector3d destinationOri);
void oneIteration(std::shared_ptr<rclcpp::Node> node);

#endif /* path_h */


