#include "Entity.h"

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

    void remove (Entity ent) {
        
    }
};