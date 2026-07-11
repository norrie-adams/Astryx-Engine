# Astryx Engine

Astryx Engine is a custom C++ engine using the OpenGL Rendering API. My goal is to release version 1.0 by August 2028.  

### Current Features
* **Clean Engine Architecture:** Modular design built from the ground up.
* **Camera System:** WASD and Mouse-look movement for 3D navigation.
* **Custom OBJ Loader:** Parses 3D models and applies textures without external heavy lifters.
* **Logging System:** A simple, lightweight utility for clean console output.

### Roadmap
* **v0.1** - [DEVELOPMENT COMPLETE] Render an OBJ File and Textures 
* **v0.2** - Assimp Integration, Lighting, and ImGui Introduction
* **v0.3** - World Management 
* **v0.4** - Animation
* **v0.5** - Full ECS System
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
* **OpenGL:** Version 3.3 (Core Profile)
* **GLFW:** Version 3.4.0 (Windowing & Input)
* **GLM:** Version 1.0.3 (OpenGL Mathematics)
* **GLAD:** Version 0.1.36 (OpenGL Loader)
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
│   ├── glad/               # Place GLAD headers here
│   ├── glfw/               # Place GLFW headers here
│   └── glm/                # Place GLM headers here
│   └── stb/                # Place stb_image.h here
├── assets/                 # Textures, shaders, models, and scripts
└── CMakeLists.txt          # Main CMake configuration file
```

