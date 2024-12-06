cmake_minimum_required(VERSION 3.8)
project(camera_ws_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find Move Packages and Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(project_utils REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED


# Add service files to transfer data
# add_service_files (
#	
# )

addexecutable(camera src/image.cpp)

# Link dependencies

ament_target_dependencies (
 camera
 rclcpp
 sensor_msgs
 control_msgs 
 project_utils
 cv_bridge
 OpenCV	
)

# Install targets
install(TARGETS camera
  DESTINATION lib/${PROJECT_NAME}
)

# Install include files
install(
  DIRECTORY 
  launch
  models
  rviz
  DESTINATION share/${PROJECT_NAME}
FILES_MATCHING PATTERN "*.launch" PATTERN "*.rviz"
)


# Ament package macros
ament_package()
