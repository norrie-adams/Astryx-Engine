#include "Game.h"
#include "ecs/components/Components.h"

void Game::createScene() {
    // Brick
    uint32_t EntityA = m_Registry->createEntity();
    m_Registry->addComponent<Transform>(EntityA, Transform{
        .position = glm::vec3(0.0f, 0.0f, 0.0f),
        .rotation = glm::vec3(0.0f, 45.0f, 0.0f),
        .scale = glm::vec3(1.0f)
    });
    m_Registry->addComponent<MeshRenderer>(EntityA, MeshRenderer{
        .modelFilePath = std::string(SANDBOX_ASSET_DIR) + "engine_cube.obj"
    });
    m_Registry->addComponent<TextureComponent>(EntityA, TextureComponent{
        .textureFilePath = std::string(SANDBOX_ASSET_DIR) + "brick_texture.jpg"
    });
    
    // Light
    uint32_t lightEntity = m_Registry->createEntity();
    m_Registry->addComponent<Light>(lightEntity, Light{
        .position = glm::vec3(5.0f, 10.0f, 5.0f),
        .color = glm::vec3(1.0f, 1.0f, 1.0f), 
        .direction = glm::vec3(-0.2f, -1.0f, -0.3f),
        .intensity = 1.0f
    });
}