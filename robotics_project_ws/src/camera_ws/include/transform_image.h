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
#include "camera_ws/srv/three_dto2_d.hpp"

class TableTransformService : public rclcpp::Node {

public:
    TableTransformService() : Node("table_transform_service");

private:
    cv::Mat perspectiveMatrix_;   // Transformation matrix
    std::vector<cv::Point2f> sourcePoints_; // Source points (3D image table corners)
    std::vector<cv::Point2f> destinationPoints_; // Destination points (2D table plane)
    rclcpp::Service<table_transform::srv::ProjectToTable>::SharedPtr service_;

    // Callback function for the service
    bool projectCallback(const std::shared_ptr<table_transform::srv::ProjectToTable::Request> req, std::shared_ptr<table_transform::srv::ProjectToTable::Response> res);

        // Assign the transformed coordinates to the response
        res.x_2d = outputPoints[0].x;
        res.y_2d = outputPoints[0].y;
        res.success = true;
        return true;
    }
};


#endif /*trasform_image.h*/
