#include "RenderSystem.h"
#include "ecs/System.h"
#include "ecs/Registry.h"
#include "ecs/Entity.h"
#include "ecs/components/Transform.h"
#include "ecs/components/MeshRenderer.h"
#include "asset/AssetManager.h"
#include "Renderer.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

System renderSystem;
AssetManager assetManager;

void RenderSystem::render(Renderer& m_Renderer, int screenWidth, int screenHeight) {
    //  ------- PASS 1 ------- 
    std::vector lights = renderSystem.matchEntites<Light>();
    auto& lightPool = m_Registry->getPool<Light>();

    // Lights
    if (!lights.empty()) {
        uint32_t lightIndex = lightPool.m_denseIndexIDs[0]; // just uses 1 for now
        Light& light = lightPool.m_componentData[lightIndex];

        Light shadowLight;
        shadowLight.position = light.position;
        shadowLight.color = light.color;
        shadowLight.direction = light.direction;
        shadowLight.intensity = light.intensity;

        m_Renderer.BeginShadowPass(shadowLight, (*m_shadowShader));
    }

    std::vector drawnEntites = renderSystem.matchEntites<Transform, MeshRenderer>();

    auto& meshRendererPool = m_Registry->getPool<MeshRenderer>();
    auto& transformPool = m_Registry->getPool<Transform>();

    for (Entity entity : drawnEntites) {
        // Get data
        uint32_t transformIndex = transformPool.m_denseIndexIDs[entity];
        uint32_t meshRendererIndex = meshRendererPool.m_denseIndexIDs[entity];

        Transform& transform = transformPool.m_componentData[transformIndex];
        MeshRenderer& meshRenderer = meshRendererPool.m_componentData[meshRendererIndex];

        // Register model and retrieve mesh
        assetHash assetKey = assetManager.registerModel(meshRenderer.modelFilePath);
        Mesh* mesh = assetManager.getMesh(assetKey);

        // Pass 1 (parameters = shadow shader, model matrix, and mesh)
        Renderer::ShadowPassParameters shadowParameters;
        shadowParameters.shadowShader = m_shadowShader.get();
        shadowParameters.model = transform.getModelMatrix();
        shadowParameters.mesh = mesh;
        m_Renderer.SubmitShadow(shadowParameters);
    }

    m_Renderer.EndShadowPass();

    // ----- PASS 2 -----
    m_Renderer.BeginScenePass((*m_sceneShader), screenWidth, screenHeight);

    for (Entity entity : drawnEntites) {
        uint32_t transformIndex = transformPool.m_denseIndexIDs[entity];
        uint32_t meshRendererIndex = meshRendererPool.m_denseIndexIDs[entity];

        Transform& transform = transformPool.m_componentData[transformIndex];
        MeshRenderer& meshRenderer = meshRendererPool.m_componentData[meshRendererIndex];

        
    }
}