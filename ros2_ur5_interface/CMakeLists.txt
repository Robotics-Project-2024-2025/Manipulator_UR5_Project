cmake_minimum_required(VERSION 3.8)
project(ros2_ur5_interface)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/SetFloat64.srv"
)

add_executable(publish_trajectory_node src/publish_trajectory_node.cpp)
add_executable(gripper_service src/gripper_service.cpp)

include_directories(
  /home/ubuntu/ros2_ws/build/move_ws/rosidl_generator_cpp
)


target_include_directories(gripper_service PRIVATE
   ${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp
   $<INSTALL_INTERFACE:include>
)

rosidl_target_interfaces(gripper_service ${PROJECT_NAME} rosidl_typesupport_cpp)

ament_target_dependencies(publish_trajectory_node
  rclcpp
  trajectory_msgs
  sensor_msgs
  control_msgs
  rclcpp_action
  std_srvs
)

ament_target_dependencies(gripper_service
  rclcpp
  ament_index_cpp
  trajectory_msgs
  sensor_msgs
  control_msgs
  rclcpp_action
  std_srvs
)

install(TARGETS
  publish_trajectory_node
  gripper_service
  DESTINATION lib/${PROJECT_NAME}
)

# Install the launch directory
install(
  DIRECTORY 
  launch
  config
  params
  gripper
  worlds
  models
  rviz
  DESTINATION share/${PROJECT_NAME}
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
