cmake_minimum_required(VERSION 3.8)
project(complete_job_ws)

# Compiler Settings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find All Packages and Dependencies

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

find_package(camera_ws REQUIRED)
# find_package(move_ws REQUIRED)

# BUILT EXECUTABLE
add_executable(complete_job src/complete_job.cpp)

ament_target_dependencies(
  complete_job
  rclcpp
)


ament_package()
