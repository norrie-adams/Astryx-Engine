#include "RenderSystem.h"
#include "ecs/System.h"
#include "ecs/Registry.h"
#include "ecs/Entity.h"
#include "ecs/components/Components.h"
#include "asset/AssetManager.h"
#include "Renderer.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

System renderSystem;
AssetManager assetManager;

void RenderSystem::render() {
    std::vector drawnEntites = renderSystem.matchEntites<Transform, MeshRenderer>(g_Registry);

    auto& transformPool = g_Registry.getPool<Transform>();
    auto& meshRendererPool = g_Registry.getPool<MeshRenderer>();

    for (Entity entity : drawnEntites) {
        // Get data
        uint32_t transformIndex = transformPool.m_denseIndexIDs[entity];
        uint32_t meshRendererIndex = meshRendererPool.m_denseIndexIDs[entity];

        Transform& transform = transformPool.m_componentData[transformIndex];
        MeshRenderer& meshRenderer = meshRendererPool.m_componentData[meshRendererIndex];

        // Register model and retrieve mesh
        assetHash assetKey = assetManager.registerModel(meshRenderer.modelFilePath);
        Mesh* mesh = assetManager.getMesh(assetKey);

        // Writes data to command
        Renderer::RenderParameters command;
        command.mesh = mesh;
        command.model = transform.getModelMatrix();
    }
}