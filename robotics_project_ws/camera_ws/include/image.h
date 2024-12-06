//
//  image.h
//  Camera
//
//  Created by Matteo Gottardelli on 06/12/24.
//

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <cmath>
#include <iostream>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
using namespace std;

using senseimage=sensor_msgs::msg::Image;
class ImageCamera : public rclcpp::Node {
public:
    ImageCamera();
    shared_ptr<const senseimage> get_image_content() const;
    void generateOutput();
    void printOnFile(string filename);
private:
    shared_ptr<rclcpp::Subscription<senseimage>> image_receiver_;
    shared_ptr<const senseimage> image_content_;
    atomic<int> counter_id{1};
};

#endif /*camera.h*/
