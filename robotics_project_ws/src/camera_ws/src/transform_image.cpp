
//
//  transform_image.h
//  Transform_image
//
//  Created by Niccolò Cristoforetti on 19/12/24.
//

#include <iostream>
#include "transform_image.h"


TableTransformService::TableTransformService() : Node("table_transform_service"){
        // Define the source and destination points
        sourcePoints_.push_back(cv::Point2f(19, 313));  // First table vertex
        sourcePoints_.push_back(cv::Point2f(175, 88));  // Second table vertex
        sourcePoints_.push_back(cv::Point2f(423, 81));  // Third table vertex
        sourcePoints_.push_back(cv::Point2f(635, 288)); // Fourth table vertex

        destinationPoints_.push_back(cv::Point2f(0, 360));  // First vertex in 2D plane
        destinationPoints_.push_back(cv::Point2f(0, 0));    // Second vertex in 2D plane
        destinationPoints_.push_back(cv::Point2f(640, 0));  // Third vertex in 2D plane
        destinationPoints_.push_back(cv::Point2f(640, 360)); // Fourth vertex in 2D plane

        // Compute the perspective transformation matrix
        perspectiveMatrix_ = cv::getPerspectiveTransform(sourcePoints_, destinationPoints_);

    // Initialize the ROS service
            service_ = this->create_service<table_transform::srv::ThreeDto2D>("ThreeDto2D", std::bind(&TableTransformService::projectCallback, this, std::placeholders::_1, std::placeholders::_2));

            RCLCPP_INFO(this->get_logger(), "Service 'ThreeDto2D' initialized.");
    }

bool TableTransformService::projectCallback(
    const std::shared_ptr<table_transform::srv::ProjectToTable::Request> req, std::shared_ptr<table_transform::srv::ProjectToTable::Response> res)
{
    // Input point in 3D space (considering only x and y)
    cv::Point2f inputPoint(req->x, req->y);

    // Transform the point to the 2D table plane
    std::vector<cv::Point2f> inputPoints = {inputPoint};
    std::vector<cv::Point2f> outputPoints;

    try
    {
        cv::perspectiveTransform(inputPoints, outputPoints, perspectiveMatrix_);
    }
    catch (const std::exception &e)
    {
        RCLCPP_ERROR(this->get_logger(), "Perspective transformation error: %s", e.what());
        res->success = false;
        return false;
    }

    if (outputPoints.empty())
    {
        res->success = false;
        return false;
    }
    
    // Assign the transformed coordinates to the response
    res->x_2d = outputPoints[0].x;
    res->y_2d = outputPoints[0].y;
    res->success = true;
    return true;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TableTransformService>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

