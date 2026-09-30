#pragma once
#include <vector>
#include <cstdint>
#include <bitset>
#include <memory>

#include "Entity.h"
#include "Component.h"

using ComponentMask = std::bitset<256>;

class ComponentIDGenerator {
    private:
        inline static uint32_t counter;
    public: 
        template <typename T>
        static uint32_t getComponentID() {
            static uint32_t id = counter++;
            return id;
        }   
};

// Test Structs
struct Transform {
    float x, y, z;
};

struct MeshRenderer {
    uint32_t AssetID;
};

struct Rigidbody {
    float Velocity;
};

class Registry {

public:
    uint32_t m_EntityCounter = 0;

    uint32_t createEntity();

    // Entity Vectors
    std::vector<Entity> m_liveEntities;
    std::vector<Entity> m_reusedIDS;
    std::vector<ComponentMask> m_EntityMasks;

    // Component Pools
    std::vector<std::unique_ptr<ISparseSet>> m_ComponentPools;

    void deleteEntity(uint32_t ID);

    template <typename T> 
    void addComponent(Entity entity, T component) {
        uint32_t componentID = ComponentIDGenerator::getComponentID<T>();
        m_EntityMasks[entity].set(componentID);
        pool = getPool<T>();
        pool.insert(entity, component);
    }

    template <typename T>
    SparseSet<T>& getPool();

};

#include "Registry.inl"