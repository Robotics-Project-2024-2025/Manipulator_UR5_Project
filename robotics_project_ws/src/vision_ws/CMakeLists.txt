cmake_minimum_required(VERSION 3.5)
project(vision_ws)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


list(APPEND CMAKE_PREFIX_PATH "/home/ubuntu/ros2_ws/install")

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(vision_ws_msgs REQUIRED)  # Find vision_ws_msgs package
find_package(rclpy REQUIRED)

# Install Python package (for ament_python)
ament_python_install_package(${PROJECT_NAME})

ament_package()

