cmake_minimum_required(VERSION 3.15) 
project(AstryxEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core graphics system driver package
find_package(OpenGL REQUIRED)

# Large dependencies fully managed via vcpkg manifest mode
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# GLAD
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)
target_link_libraries(glad PUBLIC OpenGL::GL)

# Engine sources
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(AstryxEngine ${SRC_FILES})

# Include directories
target_include_directories(AstryxEngine PRIVATE 
    src
    external/stb   
)

# Link libraries
target_link_libraries(AstryxEngine PRIVATE 
    glad                  
    glfw                  
    assimp::assimp        
    glm::glm              
    imgui::imgui          
    OpenGL::GL            
)

# Copy assets
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/test_assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
