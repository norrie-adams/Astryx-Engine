#include "Registry.h"
#include "Entity.h"
#include <iostream>
#include <cstdint>
#include <bitset>

using namespace std;

uint32_t Registry::createEntity() {
    Entity currentID = m_EntityCounter;
    m_EntityCounter++;
    return currentID;
};

void Registry::deleteEntity(uint32_t ID) {
    m_reusedIDS.push_back(ID);
    std::cout << "Deleted Entity: " << ID << endl;
}

void Registry::addComponent() {
    std::bitset<64> componentCombination;
    componentCombination.set(0);
    componentCombination.set(2);
    std::cout << "Component Bitset Combination: " << componentCombination << std::endl;
}

int main() {
    Registry registry;

    uint32_t EntityA = registry.createEntity();
    uint32_t EntityB = registry.createEntity();
    uint32_t EntityC = registry.createEntity();

    registry.deleteEntity(EntityA);

    registry.addComponent();
    
    std::cout << EntityC << std::endl;
    std::cout << EntityB << std::endl;

    return 0;
}