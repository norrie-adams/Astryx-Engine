#include "Registry.h"
#include "System.h"
#include "ecs/components/Transform.h"
#include "ecs/components/MeshRenderer.h"
#include <iostream>

// Example system so I don't forget how this works

void System::execute() {
    // Matches the entites
    std::vector<Entity> renderedEntites = System::matchEntites<Transform, MeshRenderer>();

    // Gets pools
    auto& TransformPool = m_Registry->getPool<Transform>();
    auto& MeshRendererPool = m_Registry->getPool<MeshRenderer>();

    // Loops through entites
    for (Entity entity : renderedEntites) {
        // Find dense index ids of entites
        uint32_t transformIndex = TransformPool.m_denseIndexIDs[entity];
        uint32_t meshRendererIndex = MeshRendererPool.m_denseIndexIDs[entity];

        Transform& transform = TransformPool.m_componentData[transformIndex];
        MeshRenderer& meshRenderer = MeshRendererPool.m_componentData[meshRendererIndex];

    }
}