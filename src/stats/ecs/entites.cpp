#include "scene/Registry.hpp"
#include "entites.hpp"

ECSStats ecsStats;

void clearECSStats() {
    ecsStats.entityCount = 0;
}