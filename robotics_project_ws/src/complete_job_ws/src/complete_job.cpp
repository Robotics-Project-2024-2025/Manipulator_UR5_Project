#include "complete_job.h"

bool control;
Status position_c=UNKNOWN;
Point2D blockPos;
Point2D finalPos;

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

Point2D getDestination(int class_id) {
    Eigen::Vector3f x_coords(0.3f, 0.37f, 0.45f);
    Eigen::Vector3f y_coords(0.25f, 0.15f, 0.05f);
    int row = class_id / 3;
    int col = class_id % 3;
    Point2D point;
    point.x = x_coords(col);
    point.y = y_coords(row);
    return point;
}

Point2D getDestination(int class_id) {
    Eigen::Vector3f x_coords(0.3f, 0.37f, 0.45f);
    Eigen::Vector3f y_coords(0.25f, 0.15f, 0.05f);
    int row = class_id / 3;
    int col = class_id % 3;
    Point2D point;
    point.x = x_coords(col);
    point.y = y_coords(row);
    return point;
}

void initializeBlocks(float block_x, float block_y, float dest_x, float dest_y) {
    blockPos={block_x, block_y};
    finalPos={dest_x, dest_y};
}

void determineStatus() {
    switch(position_c) {
        case UNKNOWN:
            position_c=HOME;
            break;
        case HOME:
            position_c=ABOVE_BLOCK;
            break;
        case ABOVE_BLOCK:
            position_c=BLOCK;
            break;
        case BLOCK:
            position_c=ABOVE_BLOCK_2;
            break;
        case ABOVE_BLOCK_2:
            position_c=ABOVE_DEST;
            break;
        case ABOVE_DEST:
            position_c=DEST;
            break;
        case DEST:
            position_c=ABOVE_DEST_2;
            break;
        case ABOVE_DEST_2:
            position_c=HOME;
            break;
        default:
            rclcpp::shutdown();
            exit(1);
    }
}

void oneIteration(std::shared_ptr<rclcpp::Node> node) {
    //double blockHeight = 0.5;
    double gripHeight = 0.25-0.9;
    double travelHeight = 0.5-0.9;
    double shift_x = 0.01;
    double shift_y = -0.005;
    Vector3d home{{0.4, 0.2, -0.5}};
    Vector3d aboveBlock{{blockPos.x, blockPos.y, travelHeight}};
    Vector3d block{{blockPos.x, blockPos.y, gripHeight}};
    Vector3d aboveDest{{finalPos.x, finalPos.y, travelHeight}};
    Vector3d posDest{{finalPos.x, finalPos.y, gripHeight}};
    Vector3d phiStart{{0.0, 0.0, 0.0}};
    Vector3d phiEf{{0.0, 0.0, 0.0}};
    determineStatus();
    auto gripper=std::make_shared<GripperCommunicator>();
    switch (position_c) {
        case HOME:
            gripper->close();
            std::this_thread::sleep_for(2s);
            generalizeMovement(node, home, phiEf);
            break;
        case ABOVE_BLOCK:
            gripper->open();
            std::this_thread::sleep_for(2s);
            generalizeMovement(node, aboveBlock, phiEf);
            break;
        case BLOCK:
            gripper->open();
            std::this_thread::sleep_for(2s);
            generalizeMovement(node, block, phiEf);
            break;
        case ABOVE_BLOCK_2:
            gripper->close();
            std::this_thread::sleep_for(2s);
            generalizeMovement(node, aboveBlock, phiEf);
            break;
        case ABOVE_DEST:
            gripper->close();
            std::this_thread::sleep_for(2s);
            generalizeMovement(node, aboveDest, phiEf);
            break;
        case DEST:
            gripper->close();
            std::this_thread::sleep_for(2s);
            generalizeMovement(node, posDest, phiEf);
            break;
        case ABOVE_DEST_2:
            gripper->open();
            std::this_thread::sleep_for(2s);
            generalizeMovement(node, aboveDest, phiEf);
            break;
        case UNKNOWN:
            gripper->close();
            std::this_thread::sleep_for(2s);
            generalizeMovement(node, home, phiEf);
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
    client_ = this->create_client<vision_ws_msgs::srv::Convert2din3d>("/convert_coordinates");

    // Log message to report client startup
    RCLCPP_INFO(this->get_logger(), "Conversion client ready to send requests.");
}

std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Convert2din3d::Response>> ConversionClient::sendRequest(Point2D pmin, Point2D pmax, string image_path){
    // Creating a Service Request
    auto request = std::make_shared<vision_ws_msgs::srv::Convert2din3d::Request>();
    request->upperleft.x=pmin.x;
    request->upperleft.y=pmin.y;
    request->bottomright.x=pmax.x;
    request->bottomright.y=pmax.y;
    request->image_path=image_path;
    // Verify that the service is available
    while (!client_->wait_for_service(std::chrono::seconds(10)))
    {
        RCLCPP_WARN(this->get_logger(), "Waiting for the 'Conversion from 2d to 3d' service to be available...");
    }

    // Sending the asynchronous request and returning the future
    return client_->async_send_request(request);
}

bool ConversionClient::spinUntilFutureComplete(std::shared_future<std::shared_ptr<vision_ws_msgs::srv::Convert2din3d::Response>> future){
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
