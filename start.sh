cd /home/ubuntu/ros2_ws/src/Manipulator_UR5_Project/robotics_project_ws/src/vision_ws
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install -r yolov5/requirements.txt
pip install yolov5
pip uninstall -y empy
pip install empy==3.3.4
pip install catkin_pkg
pip install lark
#pip uninstall -y ultralytics
#pip install ultralytics==7.0
pip show yolov5

#export PYTHONPATH=$PYTHONPATH:/path/to/your/.venv/lib/python3.x/site-packages
#sudo apt install python3-sdformat13


rm -r ~/ros2_ws/src/ros2_ur5_interface
cd /home/ubuntu/ros2_ws/

colcon build
source install/setup.bash

bash src/Manipulator_UR5_Project/init.sh

rosdep install -i --from-path src --rosdistro rolling -y

colcon build --packages-select complete_job_ws

source install/setup.bash

ros2 run complete_job_ws complete_job

