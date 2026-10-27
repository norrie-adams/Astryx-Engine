#include "Scene.h"
#include <memory>

Scene::Scene() {
    std::shared_ptr<Registry> globalRegistry = std::make_shared<Registry>();
};