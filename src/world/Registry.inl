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

