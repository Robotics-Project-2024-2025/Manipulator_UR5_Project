#include <rclcpp/rclcpp.hpp>
#include <vector>
#include <rclcpp_action/rclcpp_action.hpp>
#include <move_ws/srv/moving.hpp>
#include "kin_communication.h"
using namespace std;

using MoveService=move_ws::srv::Moving;

int main(int argc, const char* argv[])
{
    rclcpp::init(argc, argv);
    Matrix16 qEs;
    qEs=receive_joint_state();
    // Create a service client
    auto node=std::make_shared<rclcpp::Node>("complete_job");
    auto open_path_client_ = node->create_client<MoveService>("service_path");
    cout << "Service Starting Transition" << endl;
    // Wait for the service to become available
    while(!open_path_client_->wait_for_service(std::chrono::seconds(10))) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Path provider not available after waiting");
    }
    // Create a request and populate it
    auto request = std::make_shared<MoveService::Request>();
    request->xe1.x = 0.4;
    request->xe1.y = 0.3;
    request->xe1.z = -0.7;
    request->phie1.x = 0.0;
    request->phie1.y = 0.0;
    request->phie1.z = 0.0;
    request->joints.resize(NUM_JOINTS);
    for (int i=0; i<NUM_JOINTS; i++) {
        float val=qEs(i);
        request->joints[i]=val;
    }
    auto future=open_path_client_->async_send_request(request);
    RCLCPP_INFO(node->get_logger(), "Sending request and waiting for response...");
    if (rclcpp::spin_until_future_complete(node, future) ==
        rclcpp::FutureReturnCode::SUCCESS) {
        auto response = future.get();
        if (response->result) {
            RCLCPP_INFO(node->get_logger(), "Request completed successfully.");
        } else {
            RCLCPP_ERROR(node->get_logger(), "Error in completing the task, redo it.");
        }
    } else {
        RCLCPP_ERROR(node->get_logger(), "Failed to receive a response from the service.");
    }
    cout << "End Service" << endl;
    rclcpp::shutdown();
    return 0;
}
