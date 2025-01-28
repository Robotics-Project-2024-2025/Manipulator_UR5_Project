#!/bin/bash
source /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws/.venv/bin/activate

rm -r ~/ros2_ws/src/ros2_ur5_interface
cd /home/ubuntu/ros2_ws/

rm /home/ubuntu/ros2_ws/install/ros2_ur5_interface/share/ros2_ur5_interface/models/block*.sdf
rm /home/ubuntu/ros2_ws/install/ros2_ur5_interface/share/ros2_ur5_interface/models/block*.urdf

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select ros2_ur5_interface

source install/setup.bash
yolo="yolo.sh"
terminator -T "$yolo" -x bash -c "~/ros2_ws/src/Manipulator_UR5_Project/$yolo; exec bash" &

conversion="conversion.sh"
terminator -T "$conversion" -x bash -c "~/ros2_ws/src/Manipulator_UR5_Project/$conversion; exec bash" &

ros2 launch ros2_ur5_interface sim.launch.py #robot_ip:=192.168.1.2

