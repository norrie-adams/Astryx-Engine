#pragma once
#include <bitset>
#include <vector>
#include <cstdint>

class Registry {

public: 
    uint32_t m_EntityCounter = 0;

    uint32_t createEntity();

    std::vector<std::bitset<256>> m_entites;
};