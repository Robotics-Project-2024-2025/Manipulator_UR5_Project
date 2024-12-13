#!/bin/bash
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --symlink-install --packages-select block_spawner_ws_pkg

source install/setup.bash

ros2 run block_spawner_ws_pkg block_spawner
