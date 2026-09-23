#include "Registry.h"
#include "System.h"
#include <iostream>

TransformMask System::getTransformMask() {
    TransformMask transformMask;
    transformMask.set(ComponentIDGenerator::get<Transform>());
    return transformMask;
}

MeshRendererMask System::getMeshRendererMask() {
    MeshRendererMask meshMask;
    meshMask.set(ComponentIDGenerator::get<MeshRenderer>());
    return meshMask;
}

void System::execute(Registry& registry) {

    auto rendererMask = getMeshRendererMask() | getTransformMask();

    for (int i = 0; i < registry.m_liveEntities.size(); i++) {
        // Component Combo #1
        if ((registry.m_EntityMasks[registry.m_liveEntities[i]] & getTransformMask()) == getTransformMask()) {
            std::cout << "Entity" << " " << registry.m_liveEntities[i] << " " << "has a Transform component" << std::endl;
        }

        // Component Combo #2
        if ((registry.m_EntityMasks[registry.m_liveEntities[i]] & rendererMask) == rendererMask) {
            std::cout << "Entity" << " " << registry.m_liveEntities[i] << " " << "will be rendered at " << "X: " << registry.m_Transforms[i].x << " Y: " << registry.m_Transforms[i].y << " Z: " << registry.m_Transforms[i].z << std::endl;
        }
    }

}
 