#include <rclcpp/rclcpp.hpp>
#include <vector>
#include <rclcpp_action/rclcpp_action.hpp>
#include <move_ws/srv/moving.hpp>
#include "kin_communication.h"
using namespace std;

/*class TrajectoryActionClient : public rclcpp::Node
{
public:

    TrajectoryActionClient() : Node("trajectory_action_client")
    {
        node_executed_ = false;

        open_path_client = this->create_client<MoveService>("service_path");

        if (!open_path_client_->wait_for_service(10s)){
            RCLCPP_ERROR(this->get_logger(), "Path provider not available after waiting");
            rclcpp::shutdown();
            return;
        }

        auto request = std::make_shared<MoveService>();
        open_path_client_->async_send_request(request);        

        time_between_points_ = 0.5; // Time between points in seconds
    }

private:

    double time_between_points_; //YES
    bool node_executed_; //YES
}*/

using MoveService=move_ws::srv::Moving;
shared_ptr<const sensor_msgs::msg::JointState> joint_state_;

int main(int argc, const char* argv[])
{
    rclcpp::init(argc, argv);
    Matrix16 qEs;
    qEs=receive_joint_state();
    rclcpp::init(argc, argv);
    qEs=receive_joint_state();
    // Create a service client
    auto open_path_client_ = node->create_client<MoveService>("service_path");

    // Wait for the service to become available
    while(1) {
        if(!open_path_client_->wait_for_service(std::chrono::seconds(10))) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Path provider not available after waiting");
        }
        else {
            break;
        }
    }

    // Create a request and populate it
    auto request = std::make_shared<MoveService::Request>();
    request->xe1.x = 0.4;
    request->xe1.y = 0.3;
    request->xe1.z = -0.7;
    request->phie1.x = 0.0;
    request->phie1.y = 0.0;
    request->phie1.z = 0.0;
    for (int i=0; i<NUM_JOINTS; i++) {
        request->joints[i]=qEs(i);
    }
    // Send the request asynchronously
    rclcpp::init(argc, argv);
    auto response = std::make_shared<bool>(false);
    auto future = open_path_client_->async_send_request(
        request,
        [response](rclcpp::Client<MoveService>::SharedFuture future_response) {
            auto response_service = future_response.get();
            if (response_service->result) {
                *response = true;
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Request completed successfully.");
            } else {
                *response = false;
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Error in completing the task, redo it.");
            }
        });

    // Wait until the request completes
    rclcpp::spin_until_future_complete(node, future);

    if (*response) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Request completed successfully.");
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Error in completing the task, redo it.");
    }

    rclcpp::shutdown();
    return 0;
}
