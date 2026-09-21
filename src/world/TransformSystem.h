#pragma once
#include "Registry.h"

class TransformSystem {
public:
    TransformMask getTransformMask();
    void runSystem(Registry& registry);
};

