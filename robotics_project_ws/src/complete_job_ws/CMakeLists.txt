cmake_minimum_required(VERSION 3.8)
project(complete_job_ws)

# Compiler Settings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find All Packages and Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(move_ws REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

# Build Executable
add_executable(complete_job src/complete_job.cpp ../move_ws/src/kin_communication.cpp)

target_include_directories( complete_job PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../move_ws/include
    ${EIGEN3_INCLUDE_DIR}
)

# Link Libraries and Dependencies
ament_target_dependencies(
  complete_job
  rclcpp
  rclcpp_action
  trajectory_msgs
  sensor_msgs
  control_msgs
  move_ws
)

# Install the Executable
install(TARGETS complete_job
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
