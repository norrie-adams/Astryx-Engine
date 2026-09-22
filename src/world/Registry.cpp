#include "Registry.h"
#include "Entity.h"
#include "System.h"
#include <iostream>
#include <cstdint>
#include <bitset>
#include <string>

uint32_t Registry::createEntity() {
    Entity currentID = m_EntityCounter;
    m_EntityCounter++;
    m_liveEntities.push_back(currentID);
    m_EntityMasks.resize(currentID + 1);
    return currentID;
};

void Registry::deleteEntity(uint32_t ID) {
    m_reusedIDS.push_back(ID);
    std::cout << "Deleted Entity: " << ID << std::endl;
}

int main() {
    Registry registry;
    System system;

    uint32_t EntityA = registry.createEntity();
    uint32_t EntityB = registry.createEntity();
    uint32_t EntityC = registry.createEntity();

    registry.deleteEntity(EntityA);

    registry.addComponent<Transform>(EntityA);
    registry.addComponent<Transform>(EntityB);
    registry.addComponent<Rigidbody>(EntityB);
    registry.addComponent<MeshRenderer>(EntityA);

    std::cout << EntityC << std::endl;
    std::cout << EntityB << std::endl;

    std::cout << "EntityA Component Mask: " << registry.m_EntityMasks[EntityA] << std::endl;
    std::cout << "EntityB Component Mask: " << registry.m_EntityMasks[EntityB] << std::endl;

    system.execute(registry);

    return 0;
}
