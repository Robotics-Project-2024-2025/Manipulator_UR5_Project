#!/bin/bash
cd ~
IMAGE_NAME="pla10/ros2_ur5_interface"
if [[ "$(docker images -q $IMAGE_NAME 2> /dev/null)" == "" ]]; then
  echo "Immagine non trovata, eseguo docker pull di $IMAGE_NAME"
  docker pull $IMAGE_NAME
fi
docker network create --subnet=192.168.56.0/24 ursim_net
#bash ~/Manipulator_UR5_Project/ros2_ur5_interface/scripts/ur5.sh
bash ~/Manipulator_UR5_Project/ros2_ur5_interface/scripts/ros2.sh
