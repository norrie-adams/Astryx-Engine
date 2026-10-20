# Set Up and Building

This is

### Dependencies

* [GCC/G++](https://gcc.gnu.org/)
* [CMake](https://cmake.org/)
* [vcpkg](https://learn.microsoft.com/en-gb/vcpkg/get_started/overview)
* Any OS Specific Dependencies

### Building

While in the root of the project, run the following CMake Command:

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake
```

This runs the vcpkg setup (installing dependencies), and configures CMake. After this, run the build command:

```bash
cmake --build build
```

To launch the engine:

```bash
./build/AstryxEngine
```
