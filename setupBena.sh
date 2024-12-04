#!/usr/bin/env bash
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

rm -rf ./build ./install ./log

colcon build

source install/setup.bash
