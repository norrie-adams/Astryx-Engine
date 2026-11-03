#include "core/Application.hpp"
#include "core/Log.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/MeshRenderer.hpp"
#include "Game.h"
#include "scene/Registry.hpp"
#include <glm/glm.hpp>
#include <cstdint>
#include <string>

int main()
{
    Log::info("Engine intialized");

    Application app;

    if (!app.init())
    {
        Log::error("Application initialization failed");
        return -1;
    }

    Log::info("nanam");
    std::shared_ptr<Registry> gameRegistry = app.getRegistry();
    Log::info("nanam");
    Game game(gameRegistry);
    game.createScene();
    Log::info("nanam");

    app.run();

    return 0;
}