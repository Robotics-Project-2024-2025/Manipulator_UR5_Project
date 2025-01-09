#!/bin/bash
rm -r ~/ros2_ws/src/ros2_ur5_interface
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select gripper_ws

source install/setup.bash

ros2 run gripper_ws gripper_service 192.168.1.2
