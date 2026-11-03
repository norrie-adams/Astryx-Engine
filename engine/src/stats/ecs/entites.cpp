#include "scene/Registry.hpp"
#include "stats/ecs/entites.hpp"

ECSStats ecsStats;

void clearECSStats() {
    ecsStats.entityCount = 0;
}