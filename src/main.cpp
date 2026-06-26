#include "core/Application.h"
#include "core/Log.h"

int main()
{
    Log::info("Engine initialized");

    Application app;

    if (!app.init())
    {
        Log::error("Application initialization failed");
        return -1;
    }

    app.run();

    return 0;
}