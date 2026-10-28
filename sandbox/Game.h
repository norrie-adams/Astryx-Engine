#include "ecs/Registry.h"
#include <memory>

class Game {
    private:
        std::shared_ptr<Registry> m_Registry;

    public:
        Game(std::shared_ptr<Registry> registry) : m_Registry(registry) {};

        void createScene() {
            uint32_t EntityA = m_Registry->createEntity();

            m_Registry->addComponent<Transform>(EntityA, Transform{
                .position = glm::vec3(0.0f, 0.0f, 0.0f),
                .rotation = glm::vec3(0.0f, 45.0f, 0.0f),
                .scale = glm::vec3(1.0f)
            });
            m_Registry->addComponent<MeshRenderer>(EntityA, MeshRenderer{
                .modelFilePath = std::string(SANDBOX_ASSET_DIR) + "engine_cube.obj"
            });
        }
};