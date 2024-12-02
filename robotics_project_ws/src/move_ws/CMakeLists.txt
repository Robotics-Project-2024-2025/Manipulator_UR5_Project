cmake_minimum_required(VERSION 3.0.2)
project(move)

# Compiler Settings
add_compile_options(-std=c++11 -fpermissive)

# Find Move Packages and Dependencies
find_package(move REQUIRED COMPONENTS
  rclcpp
  project_utils
)

# Catkin Package Configuration
move_package(
  INCLUDE_DIRS include
  LIBRARIES move_robot_lib
)

# Include Directories
include_directories(
  include
)

# Build Libraries
add_library(
  src/kinematics.cpp
  src/main.cpp
)

## Declare catkin package
catkin_package()

# Building directories
include_directories(include ${catkin_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})

# Build Executables
add_executable(move main.cpp kinematics.cpp kinematics.h kin_communication.h main.cpp)

# Link Libraries
target_link_libraries(move_robot ${catkin_LIBRARIES})

# Install Targets and Headers
install(TARGETS move_robot_lib
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
