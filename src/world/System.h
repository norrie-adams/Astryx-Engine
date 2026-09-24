#pragma once
#include "Registry.h"

using TransformMask = std::bitset<256>;
using MeshRendererMask = std::bitset<256>;

class System {
public:
    TransformMask getTransformMask();
    MeshRendererMask getMeshRendererMask();
    void execute(Registry& registry);
};

