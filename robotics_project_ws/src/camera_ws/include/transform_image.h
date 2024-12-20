//
//  transform_image.h
//  Transform_image
//
//  Created by Niccolò Cristoforetti on 19/12/24.
//

#ifndef __TRANSFORM_IMAGE__
#define __TRANSFORM_IMAGE__


#include <rclcpp/rclcpp.hpp>
#include <opencv2/opencv.hpp>

class TableTransformService : public rclcpp::Node {

public:
    TableTransformService() : Node("table_transform_service");

private:
    cv::Mat perspectiveMatrix_;   // Transformation matrix
    std::vector<cv::Point2f> sourcePoints_; // Source points (3D image table corners)
    std::vector<cv::Point2f> destinationPoints_; // Destination points (2D table plane)
    rclcpp::Service<camera_ws::srv::Conversion>::SharedPtr service_;

    // Callback function for the service
    bool projectCallback(const std::shared_ptr<camera_ws::srv::Conversion::Request> req, std::shared_ptr<camera_ws::srv::Conversion::Response> res);
};


#endif /*trasform_image.h*/
