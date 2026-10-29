#include "core/Application.h"
#include "core/Log.h"
#include "ecs/components/Transform.h"
#include "ecs/components/MeshRenderer.h"
#include "Game.h"
#include "ecs/Registry.h"
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