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
find_package(OpenCV REQUIRED)

# add_message_files (FILES
#   image_processing_interfaces/msg/Point2D.msg
# )
# add_service_files(FILES
#   image_processing_interfaces/srv/DepthGet.srv
# )

add_executable(camera src/image.cpp)
add_executable(points_camera src/points.cpp)
add_executable(medium_val src/calc_medium_value.cpp)

# Include Folders

target_include_directories(camera PRIVATE
  include
  ${OpenCV_INCLUDE_DIRS}
)

target_include_directories(points_camera PRIVATE
  include
  ${OpenCV_INCLUDE_DIRS}
)

target_include_directories(medium_val PRIVATE
  include
  image_processing_interfaces/msg
  image_processing_interfaces/srv 
  ${OpenCV_INCLUDE_DIRS}
)

# Link dependencies

ament_target_dependencies (
 camera
 rclcpp
 sensor_msgs
 control_msgs 
 OpenCV
)

ament_target_dependencies (
 points_camera
 rclcpp
 sensor_msgs
 control_msgs 
 OpenCV
)

ament_target_dependencies (
 medium_val
 rclcpp
 sensor_msgs
 control_msgs 
 OpenCV
)

# Install targets
install(TARGETS camera
	points_camera
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
