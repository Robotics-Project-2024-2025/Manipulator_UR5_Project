#!/bin/bash
rm -r ~/ros2_ws/src/ros2_ur5_interface
cd ~/ros2_ws/src/Manipulator_UR5_Project

chmod +x *.sh

# Define script names
SCRIPT2="setupGazebo.sh"
SCRIPT3="yolo.sh"
SCRIPT4="conversion.sh"
SCRIPT5="completeJob.sh"

# Check if Terminator is installed
if ! command -v terminator &> /dev/null; then
    echo "Terminator not found. Please install it using: sudo apt install terminator"
    exit 1
fi

run_in_terminator() {
    local script="$1"
    terminator --new-tab -T "$script" -x bash -c "./$script; exec bash" &
    read -p "Press Enter when '$script' is done to continue..." </dev/tty
}

# Run each script in a new tab
run_in_terminator "$SCRIPT2"
run_in_terminator "$SCRIPT3"
run_in_terminator "$SCRIPT4"
run_in_terminator "$SCRIPT5"

echo "All scripts completed."
