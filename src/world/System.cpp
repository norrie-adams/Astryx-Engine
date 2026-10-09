#include "Registry.h"
#include "System.h"
#include <iostream>

void System::execute(Registry& registry) {
    // Matches the entites
    std::vector<Entity> renderedEntites = System::matchEntites<Transform, MeshRenderer>(registry);

    // Gets pools
    auto& TransformPool = registry.getPool<Transform>();
    auto& MeshRendererPool = registry.getPool<MeshRenderer>();

    // Loops through entites
    for (Entity entity : renderedEntites) {
        // Find dense index ids of entites
        uint32_t transformIndex = TransformPool.m_denseIndexIDs[entity];
        uint32_t meshRendererIndex = MeshRendererPool.m_denseIndexIDs[entity];

        Transform& transform = TransformPool.m_componentData[transformIndex];
        MeshRenderer& meshRenderer = MeshRendererPool.m_componentData[meshRendererIndex];

        std::cout << "Entity: " << entity << " will be rendered at: " << transform.x << transform.y << transform.z << "\n";
    }
}