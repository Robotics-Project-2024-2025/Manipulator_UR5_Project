#include "complete_job.h"

bool control;
int position_c=-1;
bool path_search(Vector3d xe1, Vector3d phie1, Matrix16 joint_states, std::shared_ptr<rclcpp::Node> node){
    MatrixD6 th;
    double time = 4.0;
    Matrix61 qEs;
    for (int i=0; i<NUM_JOINTS; i++) {
        qEs(i)=joint_states(i);
    }
    RCLCPP_INFO(node->get_logger(), "Checking Position");
    if(checkPosition(xe1, joint_states)) {
        if(p2pMotionPlan(qEs, xe1, phie1, time, &th)) {
            RCLCPP_INFO(node->get_logger(), "Moving to HOME");
            send_trajectory(th, node);
        }
        else {
            RCLCPP_INFO(node->get_logger(), "Error in computation of trajectory to point ");
            return false;
        }
    }
    else {
        RCLCPP_INFO(node->get_logger(), "Impossible to Reach the final Position ");
        return false;
    }
    return true;
}

void generalizeMovement (std::shared_ptr<rclcpp::Node> node, Vector3d destinationPos, Vector3d destinationOri) {
    control=false;
    Matrix16 qEs=receive_joint_state();
    control=path_search(destinationPos, destinationOri, qEs, node);
}
void oneIteration(std::shared_ptr<rclcpp::Node> node) {
    Vector3d posHome{{-0.2, 0.2, -0.3}};
    Vector3d posBlock{{-0.3, 0.4, -0.8}};
    Vector3d posDest{{0.4, 0.2, -0.7}};
    Vector3d phiStart{{0.0, 0.0, 0.0}};
    Vector3d phiEf{{0.0, 0.0, 0.0}};
    auto gripper=std::make_shared<GripperCommunicator>();
    position_c++;
    position_c=position_c%3;
    switch (position_c) {
        case 0:
            //gripper->open();
            generalizeMovement(node, posBlock, phiEf);
            break;
        case 1:
            //gripper->close();
            generalizeMovement(node, posBlock, phiEf);
            break;
        case 2:
            //gripper->open();
            generalizeMovement(node, posDest, phiEf);
            break;
        default:
            rclcpp::shutdown();
            break;
    }
}

Point2D findCenter(Point2D pmin, Point2D pmax){
    Point2D tmp;
    tmp.x = (pmax.x-pmin.x)/2 + pmin.x;
    tmp.y = (pmax.y-pmin.y)/2 + pmin.y;
    return tmp;
}

ConversionClient::ConversionClient() : Node("conversion_client"){
    // Initialization of the client service
    client_ = this->create_client<camera_ws::srv::Conversion>("/table_transform_service");

    // Log message to report client startup
    RCLCPP_INFO(this->get_logger(), "Conversion client ready to send requests.");
}

std::shared_future<std::shared_ptr<camera_ws::srv::Conversion::Response>> ConversionClient::sendRequest(int x, int y){
    // Creating a Service Request
    auto request = std::make_shared<camera_ws::srv::Conversion::Request>();
    request->x = x;
    request->y = y;

    // Verify that the service is available
    while (!client_->wait_for_service(std::chrono::seconds(10)))
    {
        RCLCPP_WARN(this->get_logger(), "Waiting for the 'Conversion' service to be available...");
    }

    // Sending the asynchronous request and returning the future
    return client_->async_send_request(request);
}

bool ConversionClient::spinUntilFutureComplete(std::shared_future<std::shared_ptr<camera_ws::srv::Conversion::Response>> future){
    // Wait until the result is available
    auto spin_result = rclcpp::spin_until_future_complete(this->get_node_base_interface(), future);

    // Checks the status of the future and returns true if completed successfully
    if (spin_result == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(this->get_logger(), "Service call completed successfully.");
        return true;
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        return false;
    }
}

YoloClient::YoloClient() : Node("yolo_client"){
    // Initialization of the client service
    client_ = this->create_client<vision_ws_msgs::srv::Boundingbox>("yolo_bounding_box_service");
    // Log message to report client startup
    RCLCPP_INFO(this->get_logger(), "Boundingbox client ready to send requests.");
}
std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Boundingbox::Response>> YoloClient::sendRequest(string image_path){
    // Creating a Service Request
    auto request = std::make_shared<vision_ws_msgs::srv::Boundingbox::Request>();
    request->image_path=image_path;
    // Verify that the service is available
    while (!client_->wait_for_service(std::chrono::seconds(10)))
    {
        RCLCPP_WARN(this->get_logger(), "Waiting for the 'Boundingbox' service to be available...");
    }
    // Sending the asynchronous request and returning the future
    return client_->async_send_request(request);
}
bool YoloClient::spinUntilFutureComplete(std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Boundingbox::Response>> future){
    // Wait until the result is available
    auto spin_result = rclcpp::spin_until_future_complete(this->get_node_base_interface(), future);
    // Checks the status of the future and returns true if completed successfully
    if (spin_result == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(this->get_logger(), "Service call completed successfully.");
        return true;
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        return false;
    }
}
