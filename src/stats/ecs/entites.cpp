#include "ecs/Registry.h"
#include "entites.h"

ECSStats ecsStats;

void clearECSStats() {
    ecsStats.entityCount = 0;
}