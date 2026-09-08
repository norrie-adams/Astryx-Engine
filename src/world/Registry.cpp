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

int main() {
    Registry registry;

    uint32_t EntityA = registry.createEntity();
    uint32_t EntityB = registry.createEntity();

    std::cout << EntityA << std::endl;
    std::cout << EntityB << std::endl;

    return 0;
}