#include "Game.h"
#include "ecs/Entity.h"
#include "ecs/components/Components.h"

void Game::createScene() {
    // Brick
    Entity Brick = m_Registry->createEntity();
    m_Registry->addComponent<Transform>(Brick, Transform{
        .position = glm::vec3(0.0f, 0.0f, 0.0f),
        .rotation = glm::vec3(0.0f, 45.0f, 0.0f),
        .scale = glm::vec3(0.7f)
    });
    m_Registry->addComponent<MeshRenderer>(Brick, MeshRenderer{
        .modelFilePath = std::string(SANDBOX_ASSET_DIR) + "engine_cube.obj"
    });
    m_Registry->addComponent<TextureComponent>(Brick, TextureComponent{
        .textureFilePath = std::string(SANDBOX_ASSET_DIR) + "brick_texture.jpg"
    });
    
    // Light
    Entity lightEntity = m_Registry->createEntity();
    m_Registry->addComponent<Light>(lightEntity, Light{
        .position = glm::vec3(5.0f, 10.0f, 5.0f),
        .color = glm::vec3(1.0f, 1.0f, 1.0f), 
        .direction = glm::vec3(-0.2f, -1.0f, -0.3f),
        .intensity = 1.0f
    });

    // Plane
    Entity Plane = m_Registry->createEntity();
    m_Registry->addComponent<Transform>(Plane, Transform{
        .position = glm::vec3(0.0f, -1.0f, 0.0f),
        .rotation = glm::vec3(0.0f, 0.0f, 0.0f),
        .scale = glm::vec3(1.0f)
    });
    m_Registry->addComponent<MeshRenderer>(Plane, MeshRenderer{
        .modelFilePath = std::string(SANDBOX_ASSET_DIR) + "engine_plane.obj"
    });
}