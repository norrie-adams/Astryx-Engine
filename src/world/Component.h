#pragma once

#include "Entity.h"
#include <vector>

class ISparseSet {
    public:
        virtual ~ISparseSet() = default;
        virtual void remove(Entity ent) = 0;
};

template <typename T> 
class SparseSet : public ISparseSet {
public:
    std::vector<int> m_denseIndexIDs;
    std::vector<Entity> m_entityIDs;
    std::vector<T> m_componentData;

    void insert (Entity ent, T component);
    void remove (Entity ent);
};

#include "Component.inl"