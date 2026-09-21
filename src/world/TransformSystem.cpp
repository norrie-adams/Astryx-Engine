#include "Registry.h"
#include "TransformSystem.h"
#include <iostream>

TransformMask TransformSystem::getTransformMask() {
    TransformMask transformMask;
    transformMask.set(ComponentIDGenerator::get<Transform>());
    return transformMask;
}

void TransformSystem::runSystem(Registry& registry) {

    for (int i = 0; i < registry.m_liveEntities.size(); i++) {
        if (registry.m_EntityMasks[registry.m_liveEntities[i]] == getTransformMask()) {
            std::cout << "Entity" << " " << registry.m_liveEntities[i] << " " << "has a Transform component" << std::endl;
        }
    }

}
