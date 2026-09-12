#include "Registry.h"
#include "Entity.h"
#include <iostream>
#include <cstdint>
#include <bitset>

// ComponentCounter decleration
uint32_t ComponentIDGenerator::counter = 0;

uint32_t Registry::createEntity() {
    Entity currentID = m_EntityCounter;
    m_EntityCounter++;
    return currentID;
};

void Registry::deleteEntity(uint32_t ID) {
    m_reusedIDS.push_back(ID);
    std::cout << "Deleted Entity: " << ID << std::endl;
}
/*
void Registry::addComponent() {
    std::bitset<64> m_componentCombination;
    m_componentCombination.set(0);
    m_componentCombination.set(2);
    std::cout << "Component Bitset Combination: " << m_componentCombination << std::endl;
} */ 

int main() {
    Registry registry;
    ComponentIDGenerator componentIDGenerator;

    uint32_t EntityA = registry.createEntity();
    uint32_t EntityB = registry.createEntity();
    uint32_t EntityC = registry.createEntity();

    registry.deleteEntity(EntityA);

    registry.addComponent<Transform>(EntityB);

    std::cout << "The ID of Entity C is: " << EntityC << std::endl;
    std::cout << "The ID of Entity B is: " << EntityB << std::endl;

    std::cout << "Transform ID is: " << componentIDGenerator.get<Transform>() << std::endl;

    return 0;
}