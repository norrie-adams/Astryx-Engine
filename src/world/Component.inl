#include "Component.h"

template <typename T>
void SparseSet<T>::insert (Entity ent, T component) {
    // resizes to match entity IDs and adds ID to the list
    if (ent >= m_denseIndexIDs.size()) {
        m_denseIndexIDs.resize(ent + 1, -1);
    }
    m_denseIndexIDs[ent] = static_cast<int>(m_componentData.size());

    // Upload actual component data
    m_componentData.push_back(component);

    // Upload entity ID
    m_entityIDs.push_back(ent);
}

template <typename T>
void SparseSet<T>::remove (Entity ent) {
    victim = m_denseIndexIDs[ent];
    replacement = m_entityIDs.back();
    replacement.
}