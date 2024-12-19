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
 ┣ robotics_project_ws          # Main package containing all other
 ┃ ┣ complete_job_ws            # Package that performs all the actions of the single packages
 ┃ ┣ move_ws                    # Package for moving the manipulator
 ┃ ┃ ┣ CMakeLists.txt           # Cmake to build the executable for moving
 ┃ ┃ ┣ package.xml              # Package Identificator
 ┃ ┃ ┣ include                  # Headers of package move_ws
 ┃ ┃ ┃ ┣ kin_communication.h    # Header for communication client-server of moving
 ┃ ┃ ┃ ┗ kinematics.h           # Header for movement functions
 ┃ ┃ ┗ src                      # Defintions of functions in header
 ┃ ┃ ┃ ┣ kin_communication.cpp  # Definitions for communication client-server of moving
 ┃ ┃ ┃ ┣ kinematics.cpp         # Definitions for movement functions
 ┃ ┃ ┃ ┗ main.cpp               # Test of movement functionality  
 | ┗  vision_ws                 # Package for vision (IN DEVELOPMENT)
 ┣ $FILES$.sh                   # Bash scripts for saving time
 ┣ ...
 ┣ Report.pdf                   # Report 
 ┗ Latex source                 # Folder with Original files from which the pdf was generated
```

[Back to top](#table-of-contents)

---

# Software Requiremets

[Back to top](#table-of-contents)

---

# Installation and Configuration

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

[Back to top](#table-of-contents)

---
