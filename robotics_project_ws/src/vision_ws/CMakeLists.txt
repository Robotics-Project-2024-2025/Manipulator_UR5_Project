cmake_minimum_required(VERSION 3.8)
project(vision_ws)

# Compiler Settings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find Move Packages and Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Generate Interfaces
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/boundingbox.srv"
  "msg/boundstruct.msg"
)




# Install the launch directory
install(
  DIRECTORY 
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

