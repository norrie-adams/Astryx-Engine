cmake_minimum_required(VERSION 3.10)

project(AstryxEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glfw)

# -----------------------------
# GLAD AS PROPER LIBRARY
# -----------------------------
add_library(glad STATIC
    external/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    external/glad/include
)

# -----------------------------
# ENGINE SOURCES
# -----------------------------
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
)

add_executable(AstryxEngine ${SRC_FILES})

# -----------------------------
# INCLUDE DIRECTORIES
# -----------------------------
target_include_directories(AstryxEngine PRIVATE
    src
    external/glfw/include
    external/glad/include
    external/glm
)

# -----------------------------
# LINK EVERYTHING
# -----------------------------
target_link_libraries(AstryxEngine PRIVATE
    glfw
    glad
)

if (WIN32)
    target_link_libraries(AstryxEngine PRIVATE opengl32)
endif()