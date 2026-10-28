find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(Engine STATIC ${ENGINE_SOURCES})

target_include_directories(Engine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}                  
    ${CMAKE_SOURCE_DIR}/external                 
)

target_link_libraries(Engine PUBLIC
    glad
    glfw
    glm::glm
    assimp::assimp
    imgui::imgui
    OpenGL::GL
)

target_include_directories(Engine PUBLIC)
file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")