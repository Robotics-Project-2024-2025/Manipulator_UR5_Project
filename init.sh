#!/bin/bash
rm -r ~/ros2_ws/src/ros2_ur5_interface
cd ~/ros2_ws/src/Manipulator_UR5_Project

chmod +x *.sh

SCRIPT1="setupVRiz.sh"
SCRIPT2="setupGazebo.sh"
SCRIPT3="testCamera.sh"
SCRIPT4="testMove.sh"
SCRIPT5="start.sh"

if ! command -v terminator &> /dev/null; then
    echo "Terminator not found. Please install it using: sudo apt install terminator"
    exit 1
fi

run_in_terminator() {
    local script="$1"
    # if [ "$script" == "$SCRIPT1" ]; then
        terminator -T "$script" -x bash -c "./$script; exec bash" &
    #else
    #     terminator --new-tab -e "bash -c './$script; exec bash'" &
   # fi
    # Wait for the user to close the Terminator window before continuing
    read -p "Press Enter when '$script' is done to continue..." </dev/tty
}

# Run each script sequentially
run_in_terminator "$SCRIPT1"
run_in_terminator "$SCRIPT2"
run_in_terminator "$SCRIPT3"
run_in_terminator "$SCRIPT4"
run_in_terminator "$SCRIPT5"

echo "All scripts completed."
