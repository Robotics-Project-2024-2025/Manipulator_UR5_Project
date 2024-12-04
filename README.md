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

#Introduction

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
