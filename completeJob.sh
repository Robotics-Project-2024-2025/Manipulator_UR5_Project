#!/bin/bash
source /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/.venv/bin/activate

rm -r ~/ros2_ws/src/ros2_ur5_interface
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select complete_job_ws

source install/setup.bash

ros2 run complete_job_ws complete_job

