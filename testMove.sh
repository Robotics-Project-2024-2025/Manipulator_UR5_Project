#!/bin/bash
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select move_ws_pkg

source install/setup.bash

ros2 run move_ws_pkg p2pmotion
