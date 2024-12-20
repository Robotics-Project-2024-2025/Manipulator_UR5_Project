cmake_minimum_required(VERSION 3.10)
project(camera_ws)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

list(APPEND CMAKE_PREFIX_PATH "/home/ubuntu/ros2_ws/install")

# Find Packages and Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)

# Generate Interfaces
rosidl_generate_interfaces(${PROJECT_NAME}
    "srv/DepthGet.srv"
  "msg/Point2D.msg"
"srv/conversion.srv"
)

# Add Executables
add_executable(camera src/image.cpp)
add_executable(points_camera src/points.cpp)
add_executable(medium_val src/calc_medium_value.cpp)
add_executable(transform_image src/transform_image.cpp)

#rosidl_target_interfaces(medium_val
#${PROJECT_NAME} "rosidl_typesupport_cpp")

rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")
target_link_libraries(medium_val
  ${cpp_typesupport_target}  # Link to the generated type support
)

# Include Directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/install/rosidl_generator_cpp
  ${OpenCV_INCLUDE_DIRS}
)

target_include_directories(camera PRIVATE
  include
  ${OpenCV_INCLUDE_DIRS}
${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp
)

target_include_directories(points_camera PRIVATE
  include
  ${OpenCV_INCLUDE_DIRS}
${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp
)

target_include_directories(medium_val PRIVATE
  include
  ${OpenCV_INCLUDE_DIRS}
${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp
)

target_include_directories(transform_image PRIVATE
  include
  ${OpenCV_INCLUDE_DIRS}
${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp
)

# Link Dependencies
ament_target_dependencies(camera
  rclcpp
  sensor_msgs
  control_msgs
  OpenCV
)

ament_target_dependencies(points_camera
  rclcpp
  sensor_msgs
  control_msgs
  OpenCV
)

ament_target_dependencies(medium_val
  rclcpp
  sensor_msgs
  control_msgs
  OpenCV
  rosidl_default_generators
rosidl_typesupport_cpp
)

ament_target_dependencies(transform_image
  rclcpp
  sensor_msgs
  control_msgs
  OpenCV
  rosidl_default_generators
rosidl_typesupport_cpp
)

target_link_libraries(medium_val
  ${rclcpp_LIBRARIES}
  ${camera_ws_LIBRARIES}  # Make sure this is pointing to the generated service type support libraries
)

# Install Targets
install(TARGETS camera points_camera medium_val
  DESTINATION lib/${PROJECT_NAME}
)

# Install Supporting Files
install(DIRECTORY launch models rviz
  DESTINATION share/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.launch" PATTERN "*.rviz"
)

# Ament Package Macros
ament_package()
