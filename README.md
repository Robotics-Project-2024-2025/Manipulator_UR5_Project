# Fundamentals of Robotics Project 2024-2025

## Table of Contents
- [Introduction](#introduction)
- [Project Layout](#project-layout)
- [Software Requiremets](#software-requirements)
- [Installation and Configuration](#installation-and-configuration)
  - [Clone Git](#clone-git)
  - [Docker](#docker)
    - [Setup Containers](#setup-containers)
    - [Setup localhost-6080](#setup-localhost-6080)
    - [Setup localhost-6081](#setup-localhost-6081)
  - [Run Project](#run-project)
- [Work Contribution](#work-contribution)
- [Contact](#contact)

---

# Introduction
This paper describes the methodology and the results achieved by a ros2 based program
that moves an UR5 robotic arm with a gripper, in order to grab and move some different
randomly spawned blocks from a random start position to a desired position. The aim of
this project is to provide a functional and correct implementation to be able to perform
the operation without encountering singularities or errors.
Different instrumentation was used to develop the project, starting from the blocks, that
have to be moved and the camera, which allows us to scan an image on which we can
perform detection and determine the position and the orientation of the objects. The
last fundamental component is the UR5 robotic arm, a lightweight arm designed for tasks
that require flexibility; it has 6 degrees of freedom and is composed by revolute joints: a
base, a shoulder, an elbow and then a spherical wrist.
Regarding the development environment, different tools were used. The first is Dock-
erDesktop which allows us to run the image provided by the professor. It is an Ubuntu
virtual machine with ros2 on it. This allows us to use node and services for communica-
tion between the different parts. The Eignen and the yolov5-pip libraries are used and
the necessary python modules are downloaded when starting the program. There is also
the Roboflow application which is used to generate pre-trained weights for the recognition
part.
The algorithm developed is divided into two main parts: vision and manipulation. The
first is responsible of scanning the camera to extract an image, process it to localize all
the blocks using Yolov5 and returning the coordinates of the bounding boxes to calculate
the relative positions. The second controls the movement of the arm to reach the given
position, grab the object, and put it in the designed position.
#Correggere grammatica<br>
#Finire layout<br>
#Togliere punto 7.<br>
#Citare il nome utente di Placido come se fosse un utente esterno<br>
#Rifinire la parte di Setup Container (ur5.sh no)<br>
#Spiegare come lanciare il bash in localhost:6081 specificando i tempi medi e cosa deve fare<br>
#Spiegare meglio Run project (prova a runnare una simulazione in modo che un utente qualunque riesca ad utilizzarlo)<br>
#Fare la tabella in Work Contribution<br>

[Back to top](#table-of-contents)

---

# Project Layout
```
Project
 ┣ robotics_project_ws             # Main package containing all other
 ┃ ┗ src                           # Folder with all our code
 ┃   ┣ camera_ws                   # Package for analyzing the images taken and extrapolate what we need for the arm
 ┃   ┃ ┣ generated                 # Analyzed images
 ┃   ┃ ┣ include                   # Headers for package camera_ws
 ┃   ┃ ┣ msg                       # Messages for communication between packages
 ┃   ┃ ┣ src                       # Definitions of functions in header
 ┃   ┃ ┃ ┣ calc_medium_value.cpp   # Definitions for ...
 ┃   ┃ ┃ ┣ image.cpp               # Definitions for ...
 ┃   ┃ ┃ ┣ points.cpp              # Definitions for ...
 ┃   ┃ ┃ ┗ transform_image.cpp     # Definitions for ...
 ┃   ┃ ┣ srv                       # Srv files for services functions
 ┃   ┃ ┣ CMakeLists.txt            # Cmake to build the executable for analyzing the images
 ┃   ┃ ┣ package.xml               # Package Identificator
 ┃   ┃ ┗ visual.py                 # View from above the table
 ┃   ┣ complete_job_ws             # Package that performs all the actions of the single packages
 ┃   ┃ ┣ include                   # Headers for 
 ┃   ┃ ┣ src                       # Definitions of functions in header
 ┃   ┃ ┃ ┣ complete_job.cpp        # Definitions for ...
 ┃   ┃ ┃ ┗ main.cpp                # Definitions for ...
 ┃   ┃ ┣ CMakeLists.txt            # Cmake to build the executable for ...
 ┃   ┃ ┗ package.xml               # Package Identificator
 ┃   ┣ move_ws                     # Package for moving the manipulator
 ┃   ┃ ┣ include                   # Headers of package move_ws
 ┃   ┃ ┃ ┣ kin_communication.h     # Header for communication client-server of moving
 ┃   ┃ ┃ ┗ kinematics.h            # Header for movement functions
 ┃   ┃ ┣ src                       # Definitions of functions in header
 ┃   ┃ ┃ ┣ kin_communication.cpp   # Definitions for communication client-server of moving
 ┃   ┃ ┃ ┣ kinematics.cpp          # Definitions for movement functions
 ┃   ┃ ┃ ┗ main.cpp                # Test of movement functionality
 ┃   ┃ ┣ CMakeLists.txt            # Cmake to build the executable for moving
 ┃   ┃ ┗ package.xml               # Package Identificator  
 ┃   ┣ vision_ws                   # Package for vision (IN DEVELOPMENT)
 ┃   ┗ vision_ws_msgs              #
 ┣ ros_ur5_interface             # Modified version of Placido's work
 ┃ ┣ config                        # configuration for the UR5 arm
 ┃ ┣ docker                        # Contains Docker setup and entrypoint for the ROS 2 UR5 interface
 ┃ ┣ gripper                       # Scripts for changing of gripper state
 ┃ ┣ images                        # 
 ┃ ┣ launch                        # Package for UR5 simulation and interaction in the gazebo 
 ┃ ┃ ┣ interface.launch.py         # Launch file to simulate the UR5 robot in gazebo
 ┃ ┃ ┗ sim.launch.py               # Launch file to interact with simulated and real UR5 robot
 ┃ ┣ models                        # URDF files and more to prepare the configuration
 ┃ ┣ params                        # Parameters file for the Gazebo bridge 
 ┃ ┣ rviz                          # RViz configuration file
 ┃ ┣ scripts                       # The two scripts mentioned in the "Setup Containers" section
 ┃ ┣ src                           # service for changing the gripper state + node for trajectory publication
 ┃ ┣ worlds                        # Gazebo world file with plugins for the UR5 simulation
 ┣ $FILES$.sh                      # Bash scripts for saving time
 ┣ ...
 ┣ Report.pdf                      # Report 
 ┗ Latex source                    # Folder with Original files from which the pdf was generated
```

The `ros2_ur5_interface is from Falqueto Placido`, also known as pla10 on GitHub ([link of the project here](https://github.com/pla10/ros2_ur5_interface.git)).
We modified some of his files to make them work better with our part.

[Back to top](#table-of-contents)

---

# Software Requirements

- The latest version of the operating system
- The latest version of Docker Desktop
- A minimum of 20GB of free space to download everything needed to run

If these prerequisites are not met, the proper functioning of this code cannot be guaranteed.


[Back to top](#table-of-contents)

---

# Installation and Configuration

For Windows, it is necessary to install WSL (Windows Subsystem for Linux) to use a Linux console on a Windows system.

WSL can be found on the Microsoft Store. From all the available versions, we chose Ubuntu 22.04.5 LTS, which can be downloaded from [here](https://apps.microsoft.com/detail/9PN20MSR04DW?hl=en-us&gl=IT&ocid=pdpshare).

When you open it for the first time, it will ask you to create a new profile by setting a nickname and password.

[Back to top](#table-of-contents)

---

## Clone Git

Done the passages above in order:

Access to you Github Account on your terminal, running:
```bash
cd ~
gh auth login
```
If it doesn't work, maybe you don't have installed gh. To install it, if you are on:<br>
MACOS • You can use homebrew. To verify that if it is already installed on your computer, run on terminal:
```bash
brew --version
```
If that doesn't put out Homebrew and the version, it does mean you haven't installed it, yet. So, to install it run:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
• Now, doing:
```bash
brew install <missing command>
```
brew will be updated and that command will be integrated in your terminal. So, install with this method gh.<br><br>

WINDOWS //// TO FILL ////<br><br>
To install gh on Windows WSL, open it and run the following command:
```bash
sudo apt update && sudo apt install -y curl && curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg && sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg && echo "deb [signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null && sudo apt update && sudo apt install -y gh && gh --version
```

2. After the command run successfully, you will have to do some choices. Select Github.com then HTTPS, type Y and press Login with a web browser and then press enter. You can use any other type of method, but I'm going to explain it how I have done it<br>
3. In the new open panel, insert the credentials and the one-time code generated on terminal and authorize the connection<br>
4. Insert your passkey and after that you will see on your terminal as last line "Logged in as<br>
5. Now run this command to clone the above repository:<br>
```bash
gh repo clone Robotics-Project-2024-2025/Manipulator_UR5_Project
```
To see, if you have successfully cloned the repository, try to access to it running:
```bash
cd Manipulator_UR5_Project
```
Now, your are in the folder.<br>

[Back to top](#table-of-contents)

---

## Docker

Click the link below:
[https://www.docker.com/products/docker-desktop](https://www.docker.com/products/docker-desktop)

Then, click on `Download Docker Desktop` and choose the software for your operating system.

If you're using windows:

After downloading it, on top  right, you'll find the settings. 
Going on
```bash
Settings -> Resources -> WSL integration
```
Click on
```bash
Enable integration with my default WSL distro
```
and then enable it for your WSL version. This will automatically link Docker Desktop to your WSL.

Remember, `Docker Desktop must be open for the project to work`.

[Back to top](#table-of-contents)

---

### Setup Containers

There are two bashes needed to run the project. They are both from placido: `ros2.sh`.

It can be found in the folder `ros2_ur5_interface/scripts`.

Modify `ros2.sh`, adding a `-v` flag after the flag `-d` in the long command line, so that it will look like this:

```bash
docker run --rm -d -v /path_of_the_project_folder:/home/ubuntu/ros2_ws/src/Manipulator_UR5_Project -p 6081:80 -p 50000-50020:50000-50020 --security-opt seccomp=unconfined --shm-size=512m --net ursim_net --ip 192.168.56.200 --name ros2 pla10/ros2_ur5_interface
```




[Back to top](#table-of-contents)

---

### Setup localhost:6081

With ros2.sh changed, run launchDocker.sh in the `robotics_project_ws` folder.

After the bash script runs, open this link in your browser to access localhost:6081:

```bash
http://localhost:6081/vnc.html
```

when the page opens, click on connect.

Now you are inside `localhost:6081`.

For windows, it may not work on WSL. 

In that case, open launchDocker.sh and change the tilde in the last line with the complete path.
Before:
```bash
bash ~/Manipulator_UR5_Project/ros2_ur5_interface/scripts/ros2.sh
```
After:
```bash
bash Linux/Ubuntu/home/"nickname"/Manipulator_UR5_Project/ros2_ur5_interface/scripts/ros2.sh
```


[Back to top](#table-of-contents)

---

## Run Project

run on the terminal the command: 
```bash
bash src/Manipulator_UR5_Project/start.sh 
```
The first time, it will install packages for around 5 minutes.

Then, the bash will prompt you to delete 3 files. Enter "Y" 3 times to accept the requests.

setupGazebo will automatically open from start.sh. It will then open two additional bash terminals, conversion.sh and yolo.sh. Return to setupGazebo, and set the number of blocks in the terminal of setupGazebo.sh.

`Do not close any of the windows created by these bashes`, otherwise the project will not work.

[Back to top](#table-of-contents)

---

# Work Contribution

| Contributors | A | B | C |
|:-------------|:-------------|:--------------:|--------------:|
| Benassi Alessandro    | a      | a      | a      |
| Calvo Daniele         | a      | a      | a      |
| Cristoforetti Niccolò | a      | a      | a      |
| Gottardelli Matteo    | a      | a      | a      |


[Back to top](#table-of-contents)

---

# Contact
- **Alessandro Benassi**  
  Email: [alessandro.benassi@studenti.unitn.it](mailto:name.surname@email.com)
- **Daniele Calvo**  
  Email: [daniele.calvo@studenti.unitn.it](mailto:name.surname@email.com)
- **Niccolò Cristoforetti**  
  Email: [n.cristoforetti@studenti.unitn.it](mailto:name.surname@email.com)
- **Matteo Gottardelli**  
  Email: [matteo.gottardelli@studenti.unitn.it](mailto:name.surname@email.com)
  
[Back to top](#table-of-contents)

---
