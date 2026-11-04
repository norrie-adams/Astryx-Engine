#include "ecs/Registry.h"
#include <memory>

class Game {
    private:
        std::shared_ptr<Registry> m_Registry;

    public:
        Game(std::shared_ptr<Registry> registry) : m_Registry(registry) {};
        void createScene();
};