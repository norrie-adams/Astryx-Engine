#pragma once
#include <vector>
#include <cstdint>
#include "Entity.h"

class ComponentIDGenerator {
    private:
        static uint32_t counter;
    public: 
        template <typename T>
        static std::uint32_t get() {
            static std::uint32_t id = counter++;
            return id;
        }   
};

// A test struct for now
struct Transform {
    float x, y, z;
};

class Registry {

public: 
    uint32_t m_EntityCounter = 0;

    uint32_t createEntity();

    std::vector<Entity> m_reusedIDS;

    void deleteEntity(uint32_t ID);

    void addComponent();
};

#include "Registry.inl"