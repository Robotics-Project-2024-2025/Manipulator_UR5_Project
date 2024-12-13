//
//  image.cpp
//  Camera
//
//  Created by Matteo Gottardelli on 06/12/24.
//

#include "image.h"
#include <filesystem>
#include <opencv2/opencv.hpp>

ImageCamera::ImageCamera() : Node("image_acquiring") {
    image_receiver_ = this->create_subscription<senseimage>(
        "/camera/image_raw/image",
        1,
        [this](std::shared_ptr<senseimage> msg) {
            image_content_ = msg;
            RCLCPP_INFO(this->get_logger(), "Received Image message");
            std::cout << "Received Image message" << std::endl;
        });

    // Wait until the image is received
    while (rclcpp::ok() && !image_content_) {
        rclcpp::spin_some(this->get_node_base_interface());
    }

    if (image_content_) {
        RCLCPP_INFO(this->get_logger(), "Successfully Received image");
        std::cout << "Successfully Received image" << std::endl;
    }
}
void ImageCamera::generateOutput() {
    string destPath="/home/ubuntu/ros2_ws/src/Project/robotics_project_ws/camera_ws/generated/";
    if (!filesystem::exists(destPath)) {
        filesystem::create_directories(destPath);
    }
    string filename = destPath + "Image" + to_string(counter_id) + ".png";
    printOnFile(filename);
    counter_id++;
}
void ImageCamera::printOnFile(string filename) {
    /*std_msgs/Header header
     uint32 height
     uint32 width
     string encoding
     uint8 is_bigendian
     uint32 step
     uint8[] data*/
    if (!image_content_) {
            cerr << "No image content available to write" << endl;
            return;
    }
    cv::Mat img(image_content_->height, image_content_->width, CV_8UC3, const_cast<uint8_t*>(image_content_->data.data()));
    cv::imwrite(filename, img);
    /*FILE* file;
    string resize_filename=filename.erase(filename.length()-4, 4) + ".txt";
    const char* cfilename=resize_filename.c_str();
    file=fopen(cfilename, "a+");
    if(file==NULL) {
        cerr << "Couldn't open or create the file" << endl;
        return;
    }
    //HEADER
    fprintf(file, "%d %d %s\n", image_content_->header.stamp.sec, image_content_->header.stamp.nanosec, image_content_->header.frame_id);
    //HEIGHT
    fprintf(file, "%d\n", image_content_->height);
    //WIDTH
    fprintf(file, "%d\n", image_content_->width);
    //ENCODING
    fprintf(file, "%s\n", image_content_->encoding);
    //IS_BIGENDIAN
    fprintf(file, "%d\n", image_content_->is_bigendian);
    //STEP
    fprintf(file, "%d\n", image_content_->step);
    //DATA
    for (int i=0; i<image_content_->height; i++) {
        for (int j=0; j<image_content_->step; j++) {
            fprintf(file, "%-3d ", image_content_->data[i+j*image_content_->step]);
        }
        fprintf(file, "\n");
    }
    fclose(file);*/
    cout << "Image saved" << endl;
}
shared_ptr<const senseimage> ImageCamera::get_image_content() const {
    return image_content_;
}
atomic<int> ImageCamera::get_counter() const{
    return counter_id.load();
}
int main (int argc, const char* argv[]) {
    rclcpp::init(argc, argv);
    cout << "Requesting Images" << endl;
    auto node=make_shared<ImageCamera>();
    while (node->get_counter()<=SAMPLES) {
        auto image_result=node->get_image_content();
        if(image_result!=NULL) {
            RCLCPP_INFO(rclcpp::get_logger("main"), "Image Received");
            node->generateOutput();
        }
        else {
            RCLCPP_WARN(rclcpp::get_logger("main"), "No Image Received.");
        }
    }
    rclcpp::shutdown();
    cout << "End Image Receiving" << endl;
    return 0;
}
