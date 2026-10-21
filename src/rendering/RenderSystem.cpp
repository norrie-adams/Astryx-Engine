#include "RenderSystem.h"
#include "ecs/System.h"
#include "ecs/Registry.h"
#include "ecs/Entity.h"
#include <vector>
#include <cstdint>

System renderSystem;

void RenderSystem::render() {
    std::vector drawnEntites = renderSystem.matchEntites<Transform, MeshRenderer>(g_Registry);

    auto& transformPool = g_Registry.getPool<Transform>();
    auto& meshRendererPool = g_Registry.getPool<MeshRenderer>();

    for (Entity entity : drawnEntites) {
        uint32_t transformIndex = transformPool.m_denseIndexIDs[entity];
        uint32_t meshRendererIndex = meshRendererPool.m_denseIndexIDs[entity];

        Transform& transform = transformPool.m_componentData[transformIndex];
        MeshRenderer& meshRenderer = meshRendererPool.m_componentData[meshRendererIndex];
    }
}