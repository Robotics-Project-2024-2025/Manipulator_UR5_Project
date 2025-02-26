#!/bin/bash
source /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/.venv/bin/activate

rm -r ~/ros2_ws/src/ros2_ur5_interface
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --symlink-install --packages-select ros2_ur5_interface

source install/setup.bash
yolo="yolo.sh"
terminator -T "$yolo" -x bash -c "~/ros2_ws/src/Manipulator_UR5_Project/$yolo; exec bash" &

ros2 launch ros2_ur5_interface interface.launch.py

