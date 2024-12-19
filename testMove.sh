#!/bin/bash
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select move_ws

source install/setup.bash

ros2 run move_ws service_moving
