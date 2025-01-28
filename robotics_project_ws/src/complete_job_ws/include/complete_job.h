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
#include "camera_ws/srv/conversion.hpp"
#include "vision_ws_msgs/srv/boundingbox.hpp"
#include "vision_ws_msgs/msg/boundstruct.hpp"
#include "vision_ws_msgs/srv/convert2din3d.hpp"
#include "vision_ws_msgs/msg/point2d.hpp"
#include "std_srvs/srv/trigger.hpp"
#include <Eigen/Dense>
#include "kin_communication.h"
#include "kinematics.h"
using namespace std;

typedef enum Status {HOME, ABOVE_BLOCK, BLOCK, ABOVE_BLOCK_2, ABOVE_DEST, DEST, ABOVE_DEST_2, UNKNOWN} Status;

typedef struct Point2D {
  float x;
  float y;
} Point2D;

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

class ConversionClient : public rclcpp::Node{
public:
    ConversionClient();

    // Function for sending an async request to the service
    std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Convert2din3d::Response>> sendRequest(Point2D pmin, Point2D pmax, string image_path);

    // Function that wait for the request to be completed
    bool spinUntilFutureComplete(std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Convert2din3d::Response>> future);

private:
    rclcpp::Client<vision_ws_msgs::srv::Convert2din3d>::SharedPtr client_; // Service client
};

class YoloClient : public rclcpp::Node{
public:
    YoloClient();

    // Function for sending an async request to the service
    std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Boundingbox::Response>> sendRequest(string image_path);

    // Function that wait for the request to be completed
    bool spinUntilFutureComplete(std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Boundingbox::Response>> future);

private:
    rclcpp::Client<vision_ws_msgs::srv::Boundingbox>::SharedPtr client_; // Service client
};
extern Status position_c;
extern Point2D blockPos;
extern Point2D finalPos;
bool path_search(Vector3d xe1, Vector3d phie1, Matrix16 joint_states, std::shared_ptr<rclcpp::Node> node);
void generalizeMovement (std::shared_ptr<rclcpp::Node> node, Vector3d destinationPos, Vector3d destinationOri);
void oneIteration(std::shared_ptr<rclcpp::Node> node);
Point2D findCenter(Point2D pmin, Point2D pmax);
void determineStatus();
void initializeBlocks(float block_x, float block_y, float dest_x, float dest_y);
#endif /* path_h */


