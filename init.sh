#!/bin/bash
cd ~/ros2_ws/src/Project
chmod +x *.sh

if ! command -v screen &> /dev/null; then
    echo "screen not found. Installation of screen happening..."
    sudo apt update
    sudo apt install screen
fi

screen -c screenrc

