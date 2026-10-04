#include "Registry.h"

// Returns a reference to a specific pool
template <typename T>
SparseSet<T>& Registry::getPool() {
    uint32_t componentID = ComponentIDGenerator::getComponentID<T>();

    if (componentID >= m_ComponentPools.size()) {
        m_ComponentPools.resize(componentID + 1);
    }

    auto& pool = m_ComponentPools[componentID];

    if (pool == nullptr) {
        pool = std::make_unique<SparseSet<T>>();
    }

    return *static_cast<SparseSet<T>*>(pool.get());
};

template <typename T> 
void Registry::addComponent(Entity ent, T component) {
    // Entity Masks
    uint32_t componentID = ComponentIDGenerator::getComponentID<T>();
    if (ent >= m_EntityMasks.size()) { // simple resize check
        m_EntityMasks.resize(ent + 1);
    }
    m_EntityMasks[ent].set(componentID);

    // Component Pools
    auto& pool = getPool<T>();
    pool.insert(ent, component);
}

template <typename T> 
bool Registry::hasComponent(Entity ent) {
    uint32_t componentID = ComponentIDGenerator::getComponentID<T>;
    return m_EntityMasks[ent].test(componentID);
}