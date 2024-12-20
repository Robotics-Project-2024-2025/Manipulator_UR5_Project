cmake_minimum_required(VERSION 3.8)
project(complete_job_ws)

# Compiler Settings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find All Packages and Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(move_ws REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

# Build Executable
add_executable(complete_job src/complete_job.cpp)

# Link Libraries and Dependencies
ament_target_dependencies(
  complete_job
  rclcpp
  move_ws
)

# Install the Executable
install(TARGETS complete_job
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
