# Astryx Engine

Astryx Engine is a custom C++ engine using the OpenGL Rendering API. My goal is to release version 1.0 by August 2028.  

> [!NOTE]
> This document was last updated November 6, 2026 during the release of v0.3, so it may be a bit outdated. If you intended to use it, please download the source code from the official release, not just cloning the GitHub Repo. 

### Current Features
* **Sparse-Set ECS:** A custom Sparse-Set ECS for maximum preformance
* **Camera System:** WASD and Mouse-look movement for 3D navigation.
* **Blinn-Phong Lighting and Shadows:** Utilizes Blinn-Phong Lighting Formulas and a dual-pass renderer for shadows
* **Debug Overlay:** ImGui overlay that displays system information and has some fun buttons
* **Logging System:** Custom logger with different tiers for clear console output
* **Sandbox-Developer Mode:** Developer enviornment for testing out new engine features and creating games/simulations

### Roadmap
* **v0.1** - [DEVELOPMENT COMPLETE] Render an OBJ File and Textures 
* **v0.2** - [DEVELOPMENT COMPLETE] Assimp Integration, Lighting, and ImGui Introduction
* **v0.3** - [DEVELOPMENT COMPLETE] ECS Transition (Includes new Sandbox developer mode)
* **v0.4** - Backend Upgrade
* **v0.5** - Animation
* **v0.6** - Physics System
* **v0.7** - Asset and Scene Pipeline
* **v0.8** - UI Overhaul
* **v0.9** - Scripting with Lua
* **v1.0** - Audio Engine and Stable Engine Release

---

### Building

See docs/BUILDING.md for build requriements. 