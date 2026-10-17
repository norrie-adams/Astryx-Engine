#pragma once

#include "Entity.h"
#include <vector>

class ISparseSet {
    public:
        virtual ~ISparseSet() = default;
        virtual void remove(Entity ent) = 0;
        virtual const std::vector<Entity>& getEntites() const = 0;
};

template <typename T> 
class SparseSet : public ISparseSet {
public:
    std::vector<int> m_denseIndexIDs;
    std::vector<Entity> m_entityIDs;
    std::vector<T> m_componentData;

    void insert (Entity ent, T component);
    void remove (Entity ent);

    const std::vector<Entity>& getEntites() const override {
        return m_entityIDs;
    }
};

#include "Component.inl"