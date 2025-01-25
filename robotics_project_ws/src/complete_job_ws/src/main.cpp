#include "complete_job.h"

int main(int argc, const char* argv[])
{
    setupCommunication(argc, argv);
    int ret_code = system("cd ~/ros2_ws");
    if (ret_code == 0) {
        std::cout << "Correct directory executed successfully.\n";
    } else {
        std::cerr << "Correct directory failed with return code: " << ret_code << '\n';
    }
    ret_code = system("colcon build");
    if (ret_code == 0) {
        std::cout << "Colcon build executed successfully.\n";
    } else {
        std::cerr << "Colcon build failed with return code: " << ret_code << '\n';
    }
    ret_code = system("source install/setup.bash");
    if (ret_code == 0) {
        std::cout << "Source executed successfully.\n";
    } else {
        std::cerr << "Source failed with return code: " << ret_code << '\n';
    }
    // Create a service client
    auto node=std::make_shared<rclcpp::Node>("complete_job");
    //Capture Image
    ret_code=system("ros2 run camera_ws camera");
    if (ret_code == 0) {
        std::cout << "Capturing Image Complete\n";
    } else {
        std::cerr << "Capturing Image Failure with return code: " << ret_code << '\n';
    }
    //CENTRAL POINT ARRAY
    Point2D center[10];
    //DETECTION FUNCTION TO IMPLEMENT IN COMPLETE_JOB USING A CLASS DETECTION
    auto nodeDetect = std::make_shared<YoloClient>();
    auto future_response_yolo = nodeDetect->sendRequest("/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/Image1.png");
    if (nodeDetect->spinUntilFutureComplete(future_response_yolo))
    {
        auto response_yolo = future_response_yolo.get();
        int counter=0;
        for (const auto& box : response_yolo->boxes)
          {
              RCLCPP_INFO(nodeDetect->get_logger(), "%d, %.2f, %.2f, %.2f, %.2f, %.2f ; ",
                          box.class_id, box.confidence, box.xmin, box.ymin, box.xmax, box.ymax);
              Point2D pmin={response_yolo->boxes[counter].xmin, response_yolo->boxes[counter].ymin};
              Point2D pmax={response_yolo->boxes[counter].xmax, response_yolo->boxes[counter].ymax};
              center[counter]=findCenter(pmin, pmax);
              counter++;
          }
        /*}
        else
        {
            RCLCPP_WARN(nodeDetect->get_logger(), "Service call succeeded but returned failure status.");
        }*/
    }
    ret_code = system("python /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/yolov5/detect.py --source /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/ --weights /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/blockTrain.pt --conf 0.7");
    if (ret_code == 0) {
        std::cout << "Bounding boxes displaying executed successfully.\n";
    } else {
        std::cerr << "Bounding boxes displaying failed with return code: " << ret_code << '\n';
    }
    //TEST TRANSFORM IMAGE
    auto nodeConv = std::make_shared<ConversionClient>();
    auto future_response = nodeConv->sendRequest(center[0].x, center[0].y);
    if (nodeConv->spinUntilFutureComplete(future_response))
    {
        auto response = future_response.get();
        if (response->success)
        {
            RCLCPP_INFO(nodeConv->get_logger(), "Transformed coordinates: x_2d=%.2f, y_2d=%.2f", response->x_2d, response->y_2d);
        }
        else
        {
            RCLCPP_WARN(nodeConv->get_logger(), "Service call succeeded but returned failure status.");
        }
    }
    //BOXES ARE GLOBALLY ACCESSIBLE BECAUSE OF oneIteration
    oneIteration(node);
    rclcpp::shutdown();
    return 0;
}
    /*auto open_path_client_ = node->create_client<MoveService>("service_path");
    cout << "Service Starting Transition" << endl;
    // Wait for the service to become available
    while(!open_path_client_->wait_for_service(std::chrono::seconds(10))) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Path provider not available after waiting");
    }
    // Create a request and populate it
    auto request = std::make_shared<MoveService::Request>();
    request->xe1.x = destinationPos(0);
    request->xe1.y = destinationPos(1);
    request->xe1.z = destinationPos(2);
    request->phie1.x = destinationOri(0);
    request->phie1.y = destinationOri(1);
    request->phie1.z = destinationOri(2);
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
            control=true;
        } else {
            RCLCPP_ERROR(node->get_logger(), "Error in completing the task, redo it.");
        }
    } else {
        RCLCPP_ERROR(node->get_logger(), "Failed to receive a response from the service.");
    }
    cout << "End Service" << endl;*/
