#!/bin/bash
source /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/.venv/bin/activate

rm -r ~/ros2_ws/src/ros2_ur5_interface
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select vision_ws_msgs

source install/setup.bash

python /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/vision_ws/detection.py
