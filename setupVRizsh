#!/usr/bin/env bash
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

rm -rf ./build ./install ./log

colcon build --packages-select ur5_simulation

source install/setup.bash

ros2 launch ur5_simulation sim.launch.py
