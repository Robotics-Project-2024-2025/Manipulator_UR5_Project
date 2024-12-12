cmake_minimum_required(VERSION 3.8)
project(block_spawner_ws_pkg)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(gazebo_dev REQUIRED)
find_package(gazebo_msgs REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(tf2 REQUIRED)

# Include directories
include_directories(
  include
  ${GAZEBO_INCLUDE_DIRS}
  ${rclcpp_INCLUDE_DIRS}
  ${gazebo_msgs_INCLUDE_DIRS}
  ${Eigen3_INCLUDE_DIRS}
  ${tf2_INCLUDE_DIRS}
)

# Libraries to link against
link_directories(
  ${GAZEBO_LIBRARY_DIRS}
)

# Add the executable
add_executable(block_spawner src/block_spawner.cpp)

# Link against required libraries
ament_target_dependencies(block_spawner
  rclcpp
  gazebo_msgs
  Eigen3
  tf2
)

target_link_libraries(block_spawner
  ${GAZEBO_LIBRARIES}
)

# Install the executable
install(TARGETS block_spawner
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch and config files if applicable
install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.launch" PATTERN "*.yaml"
)

ament_package()
