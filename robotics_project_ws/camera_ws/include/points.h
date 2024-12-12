//
//  points.h
//  Camera
//
//  Created by Danile Calvo on 12/12/24.
//

#ifndef __POINTS_H__
#define __POINTS_H__

#include <cmath>
#include <iostream>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#define SAMPLES 50
using namespace std;

using sensepoints=sensor_msgs::msg::PointCloud2;
class PointsCamera : public rclcpp::Node {
public:
    PointsCamera();
    shared_ptr<const sensepoints> get_points_content() const;
    void generateOutput();
    void printOnFile(string filename);
    atomic<int> get_counter() const;
private:
    shared_ptr<rclcpp::Subscription<sensepoints>> points_receiver_;
    shared_ptr<const sensepoints> points_content_;
    atomic<int> counter_id{1};
};

#endif /*points.h*/