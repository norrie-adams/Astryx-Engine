#pragma once
#include <cstdint>

struct ECSStats {
    uint32_t entityCount = 0;
};

void clearECSStats();

extern ECSStats ecsStats;