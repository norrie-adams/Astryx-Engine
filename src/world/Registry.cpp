#include "Registry.h"
#include "Entity.h"
#include <cstdint>
#include <bitset>
#include <iostream>

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

int main() {

    Registry registry;

    uint32_t EntityA = registry.createEntity();
    uint32_t EntityB = registry.createEntity();
    uint32_t EntityC = registry.createEntity();

    registry.deleteEntity(EntityA);

    std::cout << EntityC << std::endl;
    std::cout << EntityB << std::endl;

    return 0;
}