#!/bin/bash
cd /home/ubuntu/ros2_ws/

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select camera_ws_pkg

source install/setup.bash

ros2 run camera_ws_pkg camera
ros2 run camera_ws_pkg points_camera
ros2 run camera_ws_pkg medium_val

cd /home/ubuntu/ros2_ws/src/Project/robotics_project_ws/vision_ws/yolov5
python detect.py --source /home/ubuntu/ros2_ws/src/Project/robotics_project_ws/camera_ws/generated/ --weights /home/ubuntu/ros2_ws/src/Project/robotics_project_ws/vision_ws/blockTrain.pt --conf 0.25
