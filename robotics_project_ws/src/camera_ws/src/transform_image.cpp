
#include <iostream>
#include <transform_image.h>

// Camera parameters
struct Camera {
    double x = -0.5;      // Camera position along the X-axis
    double y = 0.5;       // Camera position along the Y-axis
    double z = 1.2;       // Camera height along the Z-axis
    double pitch = 0.4;   // Camera pitch (in radians)
    double yaw = -0.06;   // Camera yaw (in radians)
    double fov = 1.047;   // Vertical field of view (in radians, ~60 degrees)
};

// Function to calculate table dimensions based on the camera and image points
cv::Size2d calculateTableDimensions(const std::vector<cv::Point2f>& imagePoints, const Camera& cam, int imageWidth, int imageHeight) {
    // Extract table corners
    double bottom_left_x = imagePoints[0].x;
    double bottom_left_y = imagePoints[0].y;

    double top_left_x = imagePoints[1].x;
    double top_left_y = imagePoints[1].y;

    double top_right_x = imagePoints[2].x;
    double top_right_y = imagePoints[2].y;

    double bottom_right_x = imagePoints[3].x;
    double bottom_right_y = imagePoints[3].y;

    // Calculate horizontal and vertical FOV in radians
    double fov_horizontal = 2.0 * atan(tan(cam.fov / 2.0) * (static_cast<double>(imageWidth) / imageHeight));

    // Distance from the camera to the table plane
    double distance_to_plane = cam.z / cos(cam.pitch);

    // Table width (physical size)
    double table_width = 2.0 * distance_to_plane * tan(fov_horizontal / 2.0) *
                         (top_right_x - top_left_x) / imageWidth;

    // Table depth (physical size)
    double table_depth = 2.0 * distance_to_plane * tan(cam.fov / 2.0) *
                         (bottom_left_y - top_left_y) / imageHeight;

    return cv::Size2d(table_width, table_depth);
}

int main() {
    // Load the original image
    cv::Mat input = cv::imread("Image1.png");
    if (input.empty()) {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    // Define the camera parameters
    Camera cam;

    // Coordinates of the table corners in the image (in pixels)
    std::vector<cv::Point2f> imagePoints = {
        cv::Point2f(19, 313),   // Bottom-left corner
        cv::Point2f(175, 88),   // Top-left corner
        cv::Point2f(423, 81),   // Top-right corner
        cv::Point2f(635, 288)   // Bottom-right corner
    };

    // Calculate the table's physical dimensions
    cv::Size2d tableSize = calculateTableDimensions(imagePoints, cam, input.cols, input.rows);
    std::cout << "Table dimensions (width x depth): "
              << tableSize.width << "m x " << tableSize.height << "m" << std::endl;

    // Coordinates of the table in the rectified space (in meters)
    std::vector<cv::Point2f> tablePoints = {
        cv::Point2f(0.0, tableSize.height),      // Bottom-left corner
        cv::Point2f(0.0, 0.0),                   // Top-left corner
        cv::Point2f(tableSize.width, 0.0),       // Top-right corner
        cv::Point2f(tableSize.width, tableSize.height) // Bottom-right corner
    };

    // Compute the perspective transformation matrix
    cv::Mat homography = cv::getPerspectiveTransform(imagePoints, tablePoints);

    // Rectified image dimensions (e.g., 800x600 pixels)
    int output_width = 800;
    int output_height = 600;

    // Apply the perspective transformation
    cv::Mat output;
    cv::warpPerspective(input, output, homography, cv::Size(output_width, output_height));

    // Display the original and rectified images
    cv::imshow("/home/ubuntu/ros2_ws/src/Project/robotics_project_ws/src/camera_ws/generated/Image_D.png", input);
    cv::imshow("/home/ubuntu/ros2_ws/src/Project/robotics_project_ws/src/camera_ws/generated/Image_3D.png", output);

    // Save the rectified image
    cv::imwrite("/home/ubuntu/ros2_ws/src/Project/robotics_project_ws/src/camera_ws/generated/Image_D.png", output);

    cv::waitKey(0);
    return 0;
}
