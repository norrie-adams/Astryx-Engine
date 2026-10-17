#pragma once
#include "Registry.h"
#include "Component.h"
#include <bitset>
#include <iostream>
#include <algorithm>

using SystemMask = std::bitset<256>;

class System {
public:
    void execute(Registry& registry);

    template <typename... Args>
    std::vector<Entity> matchEntites(Registry& registry);
};

#include "System.inl"