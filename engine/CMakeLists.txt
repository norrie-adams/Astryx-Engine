find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

set(ENGINE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/asset/AssetManager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/asset/ModelLoader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/asset/TextureLoader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Application.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Input.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Log.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/Component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/Entity.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/System.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/components/Components.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/components/Light.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/components/MeshRenderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/components/TextureComponent.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs/components/Transform.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/memory/Arena.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering/Camera.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering/Mesh.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering/RenderSystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering/Renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering/Shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering/Texture.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/scene/Registry.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/stats/ecs/entites.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/stats/renderer/RendererStats.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui/UIManager.hpp
)

set(ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/asset/AssetManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/asset/ModelLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/asset/TextureLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/System.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/memory/Arena.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/RenderSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/Registry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stats/ecs/entites.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stats/renderer/RendererStats.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/UIManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/DebugPanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stb_implementation.cpp
)

add_library(Engine STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})

target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Engine PUBLIC
    glad
    glfw
    glm::glm
    assimp::assimp
    imgui::imgui
    OpenGL::GL
)

file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
