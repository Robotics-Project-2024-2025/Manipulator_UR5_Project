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
 ┣ $FILES$.sh                      # Bash scripts for saving time
 ┣ ...
 ┣ Report.pdf                      # Report 
 ┗ Latex source                    # Folder with Original files from which the pdf was generated
```

[Back to top](#table-of-contents)

---

# Software Requiremets

[Back to top](#table-of-contents)

---

# Installation and Configuration

For windows it's needed to install a wsl, so that it is possible to use a linux console on a windows system.
The wsl can be found on microsoft store, from all the versions we chose `Ubuntu 22.04.5 TLS`, downloadable from [here](https://apps.microsoft.com/detail/9PN20MSR04DW?hl=en-us&gl=IT&ocid=pdpshare).
After opening it for the first time, it will asks you to create a new profile, with nickname and password.

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

2. After the command run successfully, you will have to do some choices. Select Github.com then HTTPS, type Y and press Login with a web browser and then press enter. You can use any other type of method, but I'm going to explain it how I have done it<br>
3. In the new open panel, insert the credentials and the one-time code generated on terminal and authorize the connection<br>
4. Insert your passkey and after that you will see on your terminal as last line "Logged in as<br>
5. Now run this command to clone the above repository:<br>
```bash
gh repo clone Robotics-Project-2024-2025/Project
```
To see, if you have successfully cloned the repository, try to access to it running:
```bash
cd Project
```
Now, your are in the folder.<br>
7. Init and update the submodule of yolo doing:
```bash
git submodule init
git submodule update
```
//SAY TO MODIFY THE PATH IN SH ros2.sh FILE

Now, you have all the material you need on your native machine.<br><br>

[Back to top](#table-of-contents)

---

## Docker

Click the link below:
[https://www.docker.com/products/docker-desktop](https://www.docker.com/products/docker-desktop)

Then, click on `Download Docker Desktop` and choose the software you're using

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
and then enable it for your WSL version. It will automatically link DockerDesktop to your wsl

[Back to top](#table-of-contents)

---

### Setup Containers

[Back to top](#table-of-contents)

---

### Setup localhost:6080

[Back to top](#table-of-contents)

---

### Setup localhost:6081

[Back to top](#table-of-contents)

---

## Run Project

[Back to top](#table-of-contents)

---

# Work Contribution

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
