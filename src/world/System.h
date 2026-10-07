#pragma once
#include "Registry.h"
#include "Component.h"
#include <bitset>
#include <iostream>
#include <algorithm>

using SystemMask = std::bitset<256>;

class System {
public:
    void execute();

    // Test varidac template
    template<typename... Args>
    void print(Args... args) {
        (std::cout << ... << args) << '\n';
    }

    // Actual view function
    template <typename... Args>
    std::vector<Entity> matchEntites(Registry& registry) {
        std::vector<Entity> m_matchingEntites;

        // Generates target mask
        SystemMask targetMask;
        (targetMask.set(ComponentIDGenerator::getComponentID<Args>()), ...);

        // Finds the smallest pool for system iteration
        size_t poolSizes[] = { registry.getPool<Args>().m_entityIDs.size()... };
        ISparseSet* pools[] = { registry.getPool<Args>()... }; // makes a parallel array for pools
    
        auto smallestPoolIterator = std::ranges::min_element(poolSizes);
        size_t smallestIndex = std::distance(std::begin(poolSizes), smallestPoolIterator)
        ISparseSet* smallestPool = pools[smallestIndex];

        

        return m_matchingEntites;
    }
};

