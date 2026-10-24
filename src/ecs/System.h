#pragma once
#include "Registry.h"
#include "Component.h"
#include <bitset>
#include <iostream>
#include <algorithm>
#include <memory>

using SystemMask = std::bitset<256>;

class System {
private:
    std::shared_ptr<Registry> m_Registry;

public:
    void execute();

    // Put here because of weird compiler errors, may be moved back later
    template <typename... Args>
    std::vector<Entity> matchEntites() {
        std::vector<Entity> m_matchingEntites;

        // Generates target mask
        SystemMask targetMask;
        (targetMask.set(ComponentIDGenerator::getComponentID<Args>()), ...);

        // Gets the sizes of pools and actual pools for system iteration
        size_t poolSizes[] = { m_Registry->getPool<Args>().m_entityIDs.size()... };
        ISparseSet* pools[] = { &m_Registry->getPool<Args>()... }; // makes a parallel array for pools
    
        // Finds smallest pool
        auto smallestPoolIterator = std::ranges::min_element(poolSizes);
        size_t smallestIndex = std::distance(std::begin(poolSizes), smallestPoolIterator);
        ISparseSet* smallestPool = pools[smallestIndex];

        // gets the entites of the pool and loops through each one to figure out what matches
        const std::vector<Entity>& targetEntites = smallestPool->getEntites();
        for (Entity entity : targetEntites) {
            if ((m_Registry->m_EntityMasks[entity] & targetMask) == targetMask) {
                m_matchingEntites.push_back(entity);
            }
        }
            return m_matchingEntites;
        }
};

#include "System.inl"