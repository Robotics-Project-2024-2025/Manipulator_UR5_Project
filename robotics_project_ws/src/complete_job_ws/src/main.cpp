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
    //DETECTION FUNCTION TO IMPLEMENT IN COMPLETE_JOB USING A CLASS DETECTION
    auto nodeDetect = std::make_shared<YoloClient>();
    auto future_response_yolo = nodeDetect->sendRequest("/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/Image1.png");
    int counter=0;
    Point2D center;
    if (nodeDetect->spinUntilFutureComplete(future_response_yolo))
    {
        auto response_yolo = future_response_yolo.get();
        int choose=0;
        for (const auto& box : response_yolo->boxes) {
              RCLCPP_INFO(nodeDetect->get_logger(), "%d, %.2f, %.2f, %.2f, %.2f, %.2f ; ",
                          box.class_id, box.confidence, box.xmin, box.ymin, box.xmax, box.ymax);
              if(response_yolo->boxes[choose].confidence<response_yolo->boxes[counter].confidence) {
                  choose=counter;
              }
              counter++;
        }
        printf("Block choosen %d\n", choose);
        Point2D pmin={response_yolo->boxes[choose].xmin, response_yolo->boxes[choose].ymin};
        Point2D pmax={response_yolo->boxes[choose].xmax, response_yolo->boxes[choose].ymax};
        center=findCenter(pmin, pmax);
    }
    ret_code = system("python /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/yolov5/detect.py --source /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/ --weights /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/blockTrain.pt --conf 0.7");
    if (ret_code == 0) {
        std::cout << "Bounding boxes displaying executed successfully.\n";
    } else {
        std::cerr << "Bounding boxes displaying failed with return code: " << ret_code << '\n';
    }
    //TEST TRANSFORM IMAGE
    auto nodeConv = std::make_shared<ConversionClient>();
    auto future_response = nodeConv->sendRequest(center.x, center.y);
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
        //blockPos={response->x_2d, response->y_2d};
        //finalPos={0.3, 0.35};
        //BOXES ARE GLOBALLY ACCESSIBLE BECAUSE OF oneIteration
        initializeBlocks(response->x_2d, response->y_2d, 0.3, 0.35);
        oneIteration(node);
    }
    else {
        RCLCPP_INFO(node->get_logger(), "No more Blocks to move");
    }
    rclcpp::shutdown();
    return 0;
}
