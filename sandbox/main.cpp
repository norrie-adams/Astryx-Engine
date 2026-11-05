#include "core/Application.hpp"
#include "core/Log.hpp"
#include "Game.hpp"
#include "scene/Registry.hpp"

int main()
{
    Log::Info("Engine intialized");

    Application app;

    if (!app.init())
    {
        Log::Fatal("Application initialization failed");
        return -1;
    }

    Log::Info("nanam");
    std::shared_ptr<Registry> gameRegistry = app.getRegistry();
    Log::Info("nanam");
    Game game(gameRegistry);
    game.createScene();
    Log::Info("nanam");

    app.run();

    return 0;
}