cmake_minimum_required(VERSION 3.10)

project(AstryxEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# GLFW
# -----------------------------
add_subdirectory(external/glfw)

# -----------------------------
# ASSIMP
# -----------------------------

set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
add_subdirectory(external/assimp)

# -----------------------------
# GLAD
# -----------------------------
add_library(glad STATIC
    external/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    external/glad/include
)

# -----------------------------
# GLM
# -----------------------------

add_subdirectory(external/glm)

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
)

# -----------------------------
# LINK LIBRARIES
# -----------------------------
target_link_libraries(AstryxEngine PRIVATE
    glfw
    glad
    assimp
    glm
)

# Windows OpenGL library
if(WIN32)
    target_link_libraries(AstryxEngine PRIVATE opengl32)
endif()

# -----------------------------
# COPY ASSETS
# -----------------------------
file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/test_assets"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)