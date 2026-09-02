# Astryx Engine

Astryx Engine is a custom C++ engine using the OpenGL Rendering API. My goal is to release version 1.0 by August 2028.  

### Current Features
* **Model and Texture Loading:** Loads models of many different formats and textures.
* **Camera System:** WASD and Mouse-look movement for 3D navigation.
* **Blinn-Phong Lighting and Shadows:** Utilizes Blinn-Phong Lighting Formulas and a dual-pass renderer for shadows
* **Debug Overlay:** A custom overlay that displays FPS and some basic GPU information
* **Logging System:** A simple, lightweight utility for clean console output.

### Roadmap
* **v0.1** - [DEVELOPMENT COMPLETE] Render an OBJ File and Textures 
* **v0.2** - [DEVELOPMENT COMPLETE] Assimp Integration, Lighting, and ImGui Introduction
* **v0.3** - ECS Transition (Includes new Sandbox developer mode)
* **v0.4** - Backend Upgrade
* **v0.5** - Animation
* **v0.6** - Physics System
* **v0.7** - Asset and Scene Pipeline
* **v0.8** - UI Overhaul
* **v0.9** - Scripting with Lua
* **v1.0** - Audio Engine and Stable Engine Release

---

### Requirements

To compile and run this project, you will need to set up the following on your system:

#### Build Tools & Compiler
* **Compiler:** GCC / `g++` (version 14.2.0 or higher)
* **C++ Standard:** C++20
* **CMake:** Version 3.10 or higher

#### Libraries (To be downloaded/installed separately)
* **Assimp:** Version 6.0.5 (Model Loader)
* **OpenGL:** Version 3.3 (Core Profile)
* **GLFW:** Version 3.5.0 (Windowing & Input)
* **GLM:** Version 1.0.3 (OpenGL Mathematics)
* **GLAD:** Version 0.1.36 (OpenGL Loader)
* **ImGui:** Version 1.92 (UI)
* **stb_image.h:** Version 2.3 (Texture Loader) 

---

### Build Commands

Run these commands from the root directory of the project. 

##### First Time Setup
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
AstryxEngine.exe
```
**THE FOLLOWING COMMANDS MUST BE RUN INSIDE THE BUILD FOLDER** 

##### Standard Run (No Changes) 
```bash
AstryxEngine.exe
```

##### Rebuild After Code Changes (No new files created)
```bash
cmake --build .
AstryxEngine.exe
```

##### Rebuild After Adding New Files or Modifying CMakeLists.txt
```bash
cmake -G "MinGW Makefiles" ..
cmake --build .
AstryxEngine.exe
```

**NOTE: When you clone this repositiory, it will come with a text document called "compliecommands.txt". This document has all the commands listed above, and what to do if the project breaks** 

### Project Structure

```text
├── build/                  # Generated build files
├── src/                    # All engine source code (.cpp and .h files)
├── include/                # Engine header files (.hpp files)
│   ├── assimp/             # Place Assimp here
│   ├── glad/               # Place GLAD here
│   ├── glfw/               # Place GLFW here
│   └── glm/                # Place GLM here
│   └── imgui/              # Place ImGui here
│   └── stb/                # Place stb_image.h here
├── assets/                 # Textures, shaders, models, and scripts
└── CMakeLists.txt          # Main CMake configuration file
```

