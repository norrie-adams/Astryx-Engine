find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

set(ENGINE_HEADERS
    ${CMAKE_SOURCE_DIR}/include/asset/AssetManager.hpp
    ${CMAKE_SOURCE_DIR}/include/asset/ModelLoader.hpp
    ${CMAKE_SOURCE_DIR}/include/asset/TextureLoader.hpp
    ${CMAKE_SOURCE_DIR}/include/core/Application.hpp
    ${CMAKE_SOURCE_DIR}/include/core/Input.hpp
    ${CMAKE_SOURCE_DIR}/include/core/Log.hpp
    ${CMAKE_SOURCE_DIR}/include/ecs/Component.hpp
    ${CMAKE_SOURCE_DIR}/include/ecs/Entity.hpp
    ${CMAKE_SOURCE_DIR}/include/ecs/System.hpp
    ${CMAKE_SOURCE_DIR}/include/ecs/components/Components.hpp
    ${CMAKE_SOURCE_DIR}/include/ecs/components/Light.hpp
    ${CMAKE_SOURCE_DIR}/include/ecs/components/MeshRenderer.hpp
    ${CMAKE_SOURCE_DIR}/include/ecs/components/TextureComponent.hpp
    ${CMAKE_SOURCE_DIR}/include/ecs/components/Transform.hpp
    ${CMAKE_SOURCE_DIR}/include/rendering/Camera.hpp
    ${CMAKE_SOURCE_DIR}/include/rendering/Mesh.hpp
    ${CMAKE_SOURCE_DIR}/include/rendering/RenderSystem.hpp
    ${CMAKE_SOURCE_DIR}/include/rendering/Renderer.hpp
    ${CMAKE_SOURCE_DIR}/include/rendering/Shader.hpp
    ${CMAKE_SOURCE_DIR}/include/rendering/Texture.hpp
    ${CMAKE_SOURCE_DIR}/include/scene/GameObject.hpp
    ${CMAKE_SOURCE_DIR}/include/scene/Registry.hpp
    ${CMAKE_SOURCE_DIR}/include/scene/Scene.hpp
    ${CMAKE_SOURCE_DIR}/include/stats/ecs/entites.hpp
    ${CMAKE_SOURCE_DIR}/include/stats/renderer/RendererStats.hpp
)

set(ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/asset/AssetManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asset/ModelLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asset/TextureLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/System.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering/Mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering/RenderSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/GameObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/Registry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stats/ecs/entites.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stats/renderer/RendererStats.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stb_implementation.cpp
)

add_library(Engine STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})

target_include_directories(Engine
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
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
