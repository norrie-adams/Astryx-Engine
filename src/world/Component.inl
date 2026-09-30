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

// Uses "swap and pop"
template <typename T>
void SparseSet<T>::remove (Entity ent) {
    // Get proper indexs
    uint32_t victimIndex = m_denseIndexIDs[ent];
    Entity replacementIndex = m_entityIDs.back();

    // Swap
    if (victimIndex != m_entityIDs.size() - 1) {
        Entity lastSurvivor = m_entityIDs.back();

        m_entityIDs[victimIndex] = lastSurvivor;
        m_componentData[victimIndex] = m_componentData.back();

        m_denseIndexIDs[lastSurvivor] = victimIndex;
    }

    // Pop
    m_componentData.pop_back();
    m_entityIDs.pop_back();

    // Reset entity ID in sparse array
    m_denseIndexIDs[ent] = -1;
}