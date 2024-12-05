#!/usr/bin/env bash
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select ros2_ur5_interface

source install/setup.bash

ros2 launch ros2_ur5_interface sim.launch.py
