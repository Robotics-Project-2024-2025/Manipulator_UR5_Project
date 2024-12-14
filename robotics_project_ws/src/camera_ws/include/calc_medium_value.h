//
//  calc_medium_value.h
//  calc_medium_value
//
//  Created by Niccolò Cristoforetti on 12/12/24.
//

#ifndef __CALC_MEDIUM_VALUE__
#define __CALC_MEDIUM_VALUE__

#include <cmath>
#include <iostream>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "camera_ws/msg/point2_d.hpp"
#include "camera_ws/srv/depth_get.hpp"
#define SAMPLES 1
using namespace std;

typedef enum Mode {SUBSCRIBER, SERVICE};

using senseimage=sensor_msgs::msg::Image;
using serviceDepth=camera_ws::srv::DepthGet;
class ImageCamera : public rclcpp::Node {
public:
    ImageCamera(Mode mode);
    shared_ptr<const senseimage> get_image_content() const;
    void calculateDepth(
        const shared_ptr<serviceDepth::Request> request,
                   shared_ptr<serviceDepth::Response> response);
    void generateOutput();
    void printOnFile(string filename);
    atomic<int> get_counter() const;
private:
    shared_ptr<rclcpp::Subscription<senseimage>> image_receiver_;
    shared_ptr<const senseimage> image_content_;
    shared_ptr<rclcpp::Service<serviceDepth>> service_;
    atomic<int> counter_id{1};
    cv::Mat depth_image;
};

#endif /*calc_medium_value.h*/

