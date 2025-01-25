cmake_minimum_required(VERSION 3.8)
project(move_ws)

# Compiler Settings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find Move Packages and Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(Eigen3 3.3 REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_srvs REQUIRED)
find_package(camera_ws REQUIRED)
find_package(vision_ws_msgs REQUIRED)
# Generate Interfaces
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/Moving.srv"
"msg/Vector3d.msg"
)

# Build Executables
# add_executable(p2pmotion src/kinematics.cpp src/main.cpp src/kin_communication.cpp src/path.cpp)
add_executable(service_moving src/path.cpp src/kinematics.cpp src/kin_communication.cpp ../complete_job_ws/src/complete_job.cpp)

# Add Executables
rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")
target_link_libraries(service_moving
  ${cpp_typesupport_target}  # Link to the generated type support
)

# Include Directories
include_directories(
  /home/ubuntu/ros2_ws/build/move_ws/rosidl_generator_cpp
)

target_include_directories(service_moving PRIVATE
  include
  ${EIGEN3_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../complete_job_ws/include
)

# Link dependencies
# ament_target_dependencies(
#  p2pmotion
#  rclcpp
#  trajectory_msgs
#  sensor_msgs
#  control_msgs
#  rclcpp_action
# )

# Link dependencies
ament_target_dependencies(
  service_moving
  rclcpp
  std_srvs
  trajectory_msgs
  sensor_msgs
  control_msgs
  rclcpp_action
  camera_ws
  vision_ws_msgs
)

# Include directories for the target
# target_include_directories(p2pmotion PRIVATE
#  include
#  ${EIGEN3_INCLUDE_DIR}
#)

# Install targets
install(TARGETS service_moving #p2pmotion
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
ament_export_dependencies(rosidl_default_runtime)
ament_package()
