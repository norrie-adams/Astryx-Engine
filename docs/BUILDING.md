# Set Up and Building

This short guide explains to you (and me when I forget and set this up on a new device) how to configure this project

### Dependencies

* [GCC/G++](https://gcc.gnu.org/)
* [CMake](https://cmake.org/)
* [vcpkg](https://learn.microsoft.com/en-gb/vcpkg/get_started/overview)
* [Ninja](https://ninja-build.org/)
* Any OS Specific Dependencies

### Building

##### Building for VS Code

I don't use any other IDE so you need to figure that out yourself, here are some helpful links for your specific IDE: 

Visual Studio: [Microsoft Learn](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs?pivots=shell-powershell)
CLion: [CLion Documentation](https://www.jetbrains.com/help/clion/package-management.html)

1. Open the .vscode/ folder and create a settings.json file:
2. Add the following JSON configuration (**replace PATH_TO_VCPKG with the path to vcpkg on your system**):

```json
{
    "cmake.buildDirectory": "${workspaceFolder}/build",
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "PATH_TO_VCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake" 
    },
    "cmake.configureOnOpen": true,
    "cmake.generator": "Ninja" 
}
```

While in the root of the project, run the following CMake Command. This command must be run once to configure the project:

```bash
# Replace PATH_TO_VCPKG with the path to vcpkg on your system
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$PATH_TO_VCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja
```

This runs the vcpkg setup (installing dependencies), and configures CMake. After this, run the build command. Run this whenver you want to build the project:

```bash
cmake --build build
```

To launch the engine:

```bash
./build/sandbox/AstryxSandbox
```
