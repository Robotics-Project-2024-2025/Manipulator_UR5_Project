cd /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install -r yolov5/requirements.txt

rm -r ~/ros2_ws/src/ros2_ur5_interface
cd /home/ubuntu/ros2_ws/

sudo apt install python3-pip
pip3 install ultralytics

colcon build
source install/setup.bash

bash src/Manipulator_UR5_Project/init.sh

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select complete_job_ws

source install/setup.bash

ros2 run complete_job_ws complete_job
