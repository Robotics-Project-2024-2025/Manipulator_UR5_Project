//
//  points.cpp
//  Camera
//
// Created by Danile Calvo on 12/12/24.
//

#include "points.h"
#include <filesystem>
#include <opencv2/opencv.hpp>

PointsCamera::PointsCamera() : Node("points_acquiring") {
    points_receiver_ = this->create_subscription<sensepoints>(
        "/camera/image_raw/points",
        1,
        [this](std::shared_ptr<sensepoints> msg) {
            points_content_ = msg;
            RCLCPP_INFO(this->get_logger(), "Received Points message");
            std::cout << "Received Points message" << std::endl;
        });

    // Wait until the image is received
    while (rclcpp::ok() && !points_content_) {
        rclcpp::spin_some(this->get_node_base_interface());
    }

    if (points_content_) {
        RCLCPP_INFO(this->get_logger(), "Successfully Received points");
        std::cout << "Successfully Received points" << std::endl;
    }
}
void PointsCamera::generateOutput() {
    string destPath="/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/camera_ws/generated/";
    if (!filesystem::exists(destPath)) {
        filesystem::create_directories(destPath);
    }
    string filename = destPath + "Points" + to_string(counter_id) + ".png";
    printOnFile(filename);
    counter_id++;
}
void PointsCamera::printOnFile(string filename) {
    /*std_msgs/Header header
      uint32 height
      uint32 width
      sensor_msgs/PointField[] fields
      bool is_bigendian
      uint32 point_step
      uint32 row_step
      uint8[] data
      bool is_dense*/
    if (!points_content_) {
            cerr << "No points content available to write" << endl;
            return;
    }
    cv::Mat pts(points_content_->height, points_content_->width, CV_8UC3, const_cast<uint8_t*>(points_content_->data.data()));
    cv::imwrite(filename, pts);

    /*FILE* file;
    string resize_filename=filename.erase(filename.length()-4, 4) + ".txt";
    const char* cfilename=resize_filename.c_str();
    file=fopen(cfilename, "a+");
    if(file==NULL) {
        cerr << "Couldn't open or create the file" << endl;
        return;
    }
    //HEADER
    fprintf(file, "%d %d %s\n", points_content_->header.stamp.sec, points_content_->header.stamp.nanosec, points_content_->header.frame_id);
    //HEIGHT
    fprintf(file, "%d\n", points_content_->height);
    //WIDTH
    fprintf(file, "%d\n", points_content_->width);
    //ENCODING
    fprintf(file, "%s\n", points_content_->encoding);
    //IS_BIGENDIAN
    fprintf(file, "%d\n", points_content_->is_bigendian);
    //STEP
    fprintf(file, "%d\n", points_content_->step);
    //DATA
    for (int i=0; i<points_content_->height; i++) {
        for (int j=0; j<points_content_->step; j++) {
            fprintf(file, "%-3d ", points_content_->data[i+j*points_content_->step]);
        }
        fprintf(file, "\n");
    }
    fclose(file);*/
    cout << "Points saved" << endl;
}
shared_ptr<const sensepoints> PointsCamera::get_points_content() const {
    return points_content_;
}
atomic<int> PointsCamera::get_counter() const{
    return counter_id.load();
}
int main (int argc, const char* argv[]) {
    rclcpp::init(argc, argv);
    cout << "Requesting Points" << endl;
    auto node=make_shared<PointsCamera>();
    while (node->get_counter()<=SAMPLES) {
        auto points_result=node->get_points_content();
        if(points_result!=NULL) {
            RCLCPP_INFO(rclcpp::get_logger("main"), "Points Received");
            node->generateOutput();
        }
        else {
            RCLCPP_WARN(rclcpp::get_logger("main"), "No Points Received.");
        }
    }
    rclcpp::shutdown();
    cout << "End Points Receiving" << endl;
    return 0;
}
