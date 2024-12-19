//
//  transform_image.h
//  Transform_image
//
//  Created by Niccolò Cristoforetti on 19/12/24.
//

#ifndef __TRANSFORM_IMAGE__
#define __TRANSFORM_IMAGE__


#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

struct Camera {
    double x = -0.5;      // Camera position along the X-axis
    double y = 0.5;       // Camera position along the Y-axis
    double z = 1.2;       // Camera height along the Z-axis
    double pitch = 0.4;   // Camera pitch (in radians)
    double yaw = -0.06;   // Camera yaw (in radians)
    double fov = 1.047;   // Vertical field of view (in radians, ~60 degrees)
};

cv::Size2d calculateTableDimensions(const std::vector<cv::Point2f>& imagePoints, const Camera& cam, int imageWidth, int imageHeight);

#endif /*trasform_image.h*/
