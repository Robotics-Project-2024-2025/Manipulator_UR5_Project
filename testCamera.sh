#!/bin/bash
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select camera_ws

source install/setup.bash

ros2 run camera_ws camera
ros2 run camera_ws points_camera
ros2 run camera_ws medium_val

cd /home/ubuntu/ros2_ws/src/Project/robotics_project_ws/src/vision_ws/yolov5
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
sudo apt update
sudo apt install python3-xyz
python detect.py \
  --source /home/ubuntu/ros2_ws/src/Project/robotics_project_ws/src/camera_ws/generated/ \
  --weights /home/ubuntu/ros2_ws/src/Project/robotics_project_ws/src/vision_ws/blockTrain.pt \
  --conf 0.5
