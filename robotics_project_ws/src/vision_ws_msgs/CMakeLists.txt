cmake_minimum_required(VERSION 3.5)
project(vision_ws_msgs)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


list(APPEND CMAKE_PREFIX_PATH "/home/ubuntu/ros2_ws/install")

# Find dependencies
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)

# Generate interfaces (messages, services)
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Boundstruct.msg"
  "msg/Point2d.msg"
  "srv/Boundingbox.srv"
  "srv/Convert2din3d.srv"
)

ament_package()
