#!/bin/bash
rm -r ~/ros2_ws/src/ros2_ur5_interface
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select ros2_ur5_interface

source install/setup.bash

ros2 run ros2_ur5_interface gripper_service 192.168.1.2
