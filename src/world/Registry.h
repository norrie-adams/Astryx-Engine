#pragma once
#include <vector>
#include <cstdint>
#include "Entity.h"

class Registry {

public: 
    uint32_t m_EntityCounter = 0;

    uint32_t createEntity();

    std::vector<Entity> m_reusedIDS;

    void deleteEntity(uint32_t ID);
};