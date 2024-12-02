cmake_minimum_required(VERSION 3.8)
project(move)

# Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Move Packages and Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)  
find_package(project_utils REQUIRED)

# Include Directories
include_directories(include)

# Source files
set(SOURCES
  src/kinematics.cpp
  src/main.cpp
)

include_directories(include ${catkin_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})

# Build Executables
add_executable(${PROJECT_NAME} ${SOURCES})

# Link dependencies
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  std_msgs
)

# Install targets
install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

# Install include files
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

# Ament package macros
ament_package()
