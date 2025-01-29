#include "complete_job.h"

int main(int argc, const char* argv[])
{
    setupCommunication(argc, argv);
    int ret_code = system("cd ~/ros2_ws");
    if (ret_code == 0) {
        cout << "Correct directory executed successfully.\n";
    } else {
        cerr << "Correct directory failed with return code: " << ret_code << '\n';
    }
    ret_code = system("colcon build");
    if (ret_code == 0) {
        cout << "Colcon build executed successfully.\n";
    } else {
        cerr << "Colcon build failed with return code: " << ret_code << '\n';
    }
    ret_code = system("source install/setup.bash");
    if (ret_code == 0) {
        cout << "Source executed successfully.\n";
    } else {
        cerr << "Source failed with return code: " << ret_code << '\n';
    }
    int counter_blocks=0;
    // Create a service client
    while(1) {
        auto node=std::make_shared<rclcpp::Node>("complete_job");
        //Capture Image
        ret_code=system("ros2 run camera_ws camera");
        if (ret_code == 0) {
            cout << "Capturing Image Complete\n";
        } else {
            cerr << "Capturing Image Failure with return code: " << ret_code << '\n';
        }
        ret_code=system("python3 /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/visual.py");
        if (ret_code == 0) {
            cout << "Execution image Elaboration Complete\n";
        } else {
            cerr << "Image Elaboration Failure with return code: " << ret_code << '\n';
        }
        //CENTRAL POINT ARRAY
        //DETECTION FUNCTION TO IMPLEMENT IN COMPLETE_JOB USING A CLASS DETECTION
        auto nodeDetect = std::make_shared<YoloClient>();
        auto future_response_yolo = nodeDetect->sendRequest("/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/NoBack1.png");
        int counter=0;
        Point2D pmin, pmax;
        int class_id;
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
            pmin={response_yolo->boxes[choose].xmin, response_yolo->boxes[choose].ymin};
            pmax={response_yolo->boxes[choose].xmax, response_yolo->boxes[choose].ymax};
            class_id=response_yolo->boxes[choose].class_id;
        }
        
        //TEST TRANSFORM IMAGE
        auto nodeConv = std::make_shared<ConversionClient>();
        
        auto future_response = nodeConv->sendRequest(pmin, pmax, "/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/OnlyBlocks1.png");
        if (nodeConv->spinUntilFutureComplete(future_response))
        {
            auto response = future_response.get();
            if (response->success)
            {
                RCLCPP_INFO(nodeConv->get_logger(), "Transformed coordinates: x_3d=%.2f, y_3d=%.2f, z_3d=%2f, rot=%.2f", response->x, response->y, response->z, response->rotation); //response->rotation is yaw
            }
            else
            {
                RCLCPP_WARN(nodeConv->get_logger(), "Service call succeeded but returned failure status.");
            }
            //blockPos={response->x_2d, response->y_2d};
            //finalPos={0.3, 0.35};
            //BOXES ARE GLOBALLY ACCESSIBLE BECAUSE OF oneIteration
            double roll=0.0;
            double pitch=0.0;
            double yaw=response->rotation;
            Eigen::Quaterniond q=Quaterniond(roll, pitch, yaw, 1.0);
            Eigen::Vector3d euler = q.toRotationMatrix().eulerAngles(2,1,0);
            double startFrameZ = -euler(2);
            cout << euler << std::endl;
            if (areEqual(startFrameZ, M_PI, 0.001)){
                startFrameZ = 0;
            }
            cout << startFrameZ << std::endl;
            Point2D destination = getDestination(counter_blocks);//Point2D destination = getDestination(class_id);
            initializeBlocks(response->x, response->y, destination.x, destination.y, startFrameZ);
        }
        else {
            RCLCPP_INFO(node->get_logger(), "Infinite elaboration error");
            rclcpp::shutdown();
            return 0;
        }
        oneIteration(node);
        counter_blocks++;
    }
    rclcpp::shutdown();
    return 0;
}
