cmake_minimum_required(VERSION 3.8)
project(block_spawner_ws_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(rclcpp REQUIRED)
find_package(ros2_control REQUIRED)  # Ensure this is found if using ROS 2 control
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(ros_gz_sim REQUIRED)  # For Gazebo simulation integration
find_package(gz-sim8 REQUIRED)


add_executable(block_spawn src/block_spawn.cpp)

ament_target_dependencies(block_spawn
  rclcpp
  ros2_control
  ros_gz_sim
  gz-sim8
)

install(TARGETS block_spawn
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
