
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
        sourcePoints_.push_back(cv::Point2f(0, 0));  // First table vertex
        sourcePoints_.push_back(cv::Point2f(640, 0));  // Second table vertex
        sourcePoints_.push_back(cv::Point2f(0, 360));  // Third table vertex
        sourcePoints_.push_back(cv::Point2f(640, 360)); // Fourth table vertex

        destinationPoints_.push_back(cv::Point2f(175, 88));  // First vertex in 2D plane
        destinationPoints_.push_back(cv::Point2f(423, 81));    // Second vertex in 2D plane
        destinationPoints_.push_back(cv::Point2f(19, 313));  // Third vertex in 2D plane
        destinationPoints_.push_back(cv::Point2f(635, 288)); // Fourth vertex in 2D plane

        // Compute the perspective transformation matrix
        perspectiveMatrix_ = cv::getPerspectiveTransform(destinationPoints_, sourcePoints_);

    // Initialize the ROS service
            service_ = this->create_service<camera_ws::srv::Conversion>("table_transform_service", std::bind(&TableTransformService::projectCallback, this, std::placeholders::_1, std::placeholders::_2));

            RCLCPP_INFO(this->get_logger(), "Service 'Conversion' ended");
    }

bool TableTransformService::projectCallback(
    const std::shared_ptr<camera_ws::srv::Conversion::Request> req, std::shared_ptr<camera_ws::srv::Conversion::Response> res)
{
    // Input point in 3D space (considering only x and y)
    cv::Point2f inputPoint(cv::Point(req->x, req->y));

    // Transform the point to the 2D table plane
    std::vector<cv::Point2f> inputPoints;
    std::vector<cv::Point2f> outputPoints;
    inputPoints.push_back(inputPoint);

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
    float minX, minY, maxX, maxY;
    minX=std::min(TABLE_BOTTOM_RIGHT_X, TABLE_TOP_LEFT_X);
    minY=std::min(TABLE_BOTTOM_RIGHT_Y, TABLE_TOP_LEFT_Y);
    maxX=std::max(TABLE_BOTTOM_RIGHT_X, TABLE_TOP_LEFT_X);
    maxY=std::max(TABLE_BOTTOM_RIGHT_Y, TABLE_TOP_LEFT_Y);
    // Assign the transformed coordinates to the response
    res->x_2d = outputPoints[0].x;
    res->y_2d = outputPoints[0].y;
    res->success = true;
    res->x_2d = maxX-(float)((float)outputPoints[0].y/360)*(maxX-minX);
    res->y_2d = maxY-(float)((float)outputPoints[0].x/640)*(maxY-minY);
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

