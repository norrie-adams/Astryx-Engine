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
add_library(glm INTERFACE)

target_include_directories(glm INTERFACE
    external/glm
)

# -----------------------------
# IMGUI
# -----------------------------

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/imgui")

add_library(imgui STATIC
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_link_libraries(imgui PRIVATE glfw glad)

target_include_directories(imgui PUBLIC 
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
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
)

# -----------------------------
# LINK LIBRARIES
# -----------------------------
target_link_libraries(AstryxEngine PRIVATE
    glfw
    glad
    assimp
    glm
    imgui
)
# -----------------------------
# WINDOWS OPENGL LIBRARY
#------------------------------

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