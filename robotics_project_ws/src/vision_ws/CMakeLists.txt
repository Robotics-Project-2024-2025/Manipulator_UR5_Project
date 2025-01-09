cmake_minimum_required(VERSION 3.8)
project(vision_ws)

# Compiler Settings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

list(APPEND CMAKE_PREFIX_PATH "/home/ubuntu/ros2_ws/install")

# Find Move Packages and Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Generate Interfaces
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/boundingbox.srv"
"msg/boundstruct.msg"
)

# Build Executables
add_executable(service_vision src/main.cpp)


# Include Directories
include_directories(
  /home/ubuntu/ros2_ws/build/vision_ws/rosidl_generator_cpp
)

target_include_directories(service_vision PRIVATE
  include
${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp
)

# Link dependencies
ament_target_dependencies(
  service_vision
  rclcpp
)

# Install targets
# install(TARGETS service_...
#   DESTINATION lib/${PROJECT_NAME}
# )


# Install the launch directory
install(
  DIRECTORY 
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

