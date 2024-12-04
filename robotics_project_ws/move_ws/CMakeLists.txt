cmake_minimum_required(VERSION 3.8)
project(move_ws_pkg)

# Compiler Settings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find Move Packages and Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(Eigen3 3.3 REQUIRED)

# Build Executables
add_executable(p2pmotion src/kinematics.cpp src/main.cpp src/kin_communication.cpp)

# Link dependencies
ament_target_dependencies(
  p2pmotion
  rclcpp
 trajectory_msgs
sensor_msgs
)

# Include directories for the target
target_include_directories(p2pmotion PRIVATE
  include
  ${EIGEN3_INCLUDE_DIR}
)

# Install targets
install(TARGETS p2pmotion
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
