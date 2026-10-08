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

    // Actual view function
    template <typename... Args>
    std::vector<Entity> matchEntites(Registry& registry) {
        std::vector<Entity> m_matchingEntites;

        // Generates target mask
        SystemMask targetMask;
        (targetMask.set(ComponentIDGenerator::getComponentID<Args>()), ...);

        // Gets the sizes of pools and actual pools for system iteration
        size_t poolSizes[] = { registry.getPool<Args>().m_entityIDs.size()... };
        ISparseSet* pools[] = { registry.getPool<Args>()... }; // makes a parallel array for pools
    
        // Finds smallest pool
        auto smallestPoolIterator = std::ranges::min_element(poolSizes);
        size_t smallestIndex = std::distance(std::begin(poolSizes), smallestPoolIterator)
        ISparseSet* smallestPool = pools[smallestIndex];

        // gets the entites of the pool and loops through each one to figure out what matches
        const std::vector<Entity>& targetEntites = smallestPool->getEntites();
        for (Entity entity : targetEntites) {
            if ((registry.m_EntityMasks[entity] & targetMask) == targetMask) {
                m_matchingEntites.push_back(entity);
            }
        }

        return m_matchingEntites;
    }
};

