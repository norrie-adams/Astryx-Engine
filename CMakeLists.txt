cmake_minimum_required(VERSION 3.15) 
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(AstryxEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Core graphics system driver package
find_package(OpenGL REQUIRED)

# GLAD
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)
target_link_libraries(glad PUBLIC OpenGL::GL)

# Santaizer
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

add_subdirectory(src)

option(BUILD_SANDBOX "Build the sandbox developer mode application" ON)
option(BUILD_TESTS "Build the unit tests" ON)

# Enables the built-in CTest testing framework
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()