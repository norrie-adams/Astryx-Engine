#include "Registry.h"
#include "Entity.h"
#include "System.h"
#include <iostream>
#include <cstdint>
#include <bitset>
#include <string>
#include <queue>

Entity Registry::createEntity() {
    if (m_reusedEntities.size() != 0) {
        Entity id = m_reusedEntities.front();
        return id;
    }
    Entity id = m_EntityCounter;
    m_EntityCounter++;
    m_liveEntities.push_back(id);
    m_EntityMasks.resize(id + 1);
    return id;
};

void Registry::deleteEntity(Entity entity) {
    // Entity
    m_EntityMasks[entity].reset();
    m_reusedEntities.push(entity);
    // Component
    for (auto& pool : m_ComponentPools) {
        if (pool != nullptr) {
            pool->remove(entity);
        }
    }
    // Test
    std::cout << "Deleted Entity: " << entity << std::endl;
}

int main() {
    Registry registry;
    System system;

    uint32_t EntityA = registry.createEntity();
    uint32_t EntityB = registry.createEntity();
    uint32_t EntityC = registry.createEntity();

    std::cout << EntityA << std::endl;
    std::cout << EntityB << std::endl;

    std::cout << "EntityA Component Mask: " << registry.m_EntityMasks[EntityA] << std::endl;
    std::cout << "EntityB Component Mask: " << registry.m_EntityMasks[EntityB] << std::endl;

    registry.addComponent<Transform>(EntityA, Transform {10.0f, 10.0f, 10.0f});
    registry.addComponent<MeshRenderer>(EntityA, MeshRenderer {29});

    registry.addComponent<Transform>(EntityB, Transform {10.0f, 40.0f, 19.0f});

    system.execute(registry);

    return 0;
}
