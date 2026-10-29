#include "RenderSystem.h"
#include "ecs/System.h"
#include "ecs/Registry.h"
#include "ecs/Entity.h"
#include "ecs/components/Transform.h"
#include "ecs/components/MeshRenderer.h"
#include "ecs/components/Light.h"
#include "ecs/components/TextureComponent.h"
#include "asset/AssetManager.h"
#include "stats/renderer/RendererStats.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "core/Log.h"

void RenderSystem::render(Renderer& m_Renderer, int screenWidth, int screenHeight) {    
    //  ------- PASS 1 ------- 
    std::vector<Entity> lights = System::matchEntites<Light>();
    auto& lightPool = m_Registry->getPool<Light>();
    uint32_t lightIndex = 0;
    bool mainLightExists = false;

    // Lights
    if (!lights.empty()) {
        // Just uses 1 main light for now
        Light& light = lightPool.m_componentData[lightIndex];
        mainLightExists = true;

        Light shadowLight;
        shadowLight.position = light.position;
        shadowLight.color = light.color;
        shadowLight.direction = light.direction;
        shadowLight.intensity = light.intensity;

        m_Renderer.BeginShadowPass(shadowLight, (*m_shadowShader));
    }

    std::vector<Entity> drawnEntites = System::matchEntites<Transform, MeshRenderer>();

    auto& meshRendererPool = m_Registry->getPool<MeshRenderer>();
    auto& transformPool = m_Registry->getPool<Transform>();

    for (Entity entity : drawnEntites) {
        // Get data
        uint32_t transformIndex = transformPool.m_denseIndexIDs[entity];
        uint32_t meshRendererIndex = meshRendererPool.m_denseIndexIDs[entity];

        Transform& transform = transformPool.m_componentData[transformIndex];
        MeshRenderer& meshRenderer = meshRendererPool.m_componentData[meshRendererIndex];

        // Register model and retrieve mesh
        assetHash assetKey = m_AssetManager.registerModel(meshRenderer.modelFilePath);
        Mesh* mesh = m_AssetManager.getMesh(assetKey);

        // pass in parameters
        Renderer::ShadowPassParameters shadowParameters;
        shadowParameters.shadowShader = m_shadowShader.get();
        shadowParameters.model = transform.getModelMatrix();
        shadowParameters.mesh = mesh;
        m_Renderer.SubmitShadow(shadowParameters);
    }

    if (mainLightExists) {
        m_Renderer.EndShadowPass();
    }

    // ----- PASS 2 -----
    m_Renderer.BeginScenePass((*m_sceneShader), screenWidth, screenHeight);

    // Textures
    auto& texturePool = m_Registry->getPool<TextureComponent>();

    for (Entity entity : drawnEntites) {
        rendererStats.drawCalls = 0;
        Renderer::MainPassParameters sceneParameters;

        // Gets pools and checks if texture exists
        uint32_t transformIndex = transformPool.m_denseIndexIDs[entity];
        uint32_t meshRendererIndex = meshRendererPool.m_denseIndexIDs[entity];

        if (m_Registry->hasComponent<TextureComponent>(entity)) {
            uint32_t textureIndex = texturePool.m_denseIndexIDs[entity];
            TextureComponent& textureData = texturePool.m_componentData[textureIndex];
            assetHash textureKey = m_AssetManager.registerTexture(textureData.textureFilePath);
            Texture* texture = m_AssetManager.getTexture(textureKey);
            sceneParameters.texture = texture;
        }

        Transform& transform = transformPool.m_componentData[transformIndex];
        MeshRenderer& meshRenderer = meshRendererPool.m_componentData[meshRendererIndex];

        assetHash assetKey = m_AssetManager.registerModel(meshRenderer.modelFilePath);
        Mesh* mesh = m_AssetManager.getMesh(assetKey);

        // View and Projection Matrices
        glm::mat4 view = m_Camera.getViewMatrix(); // View transform (camera space)
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f); // Perspective projection
        glm::vec3 camPos = m_Camera.getPosition();                        // ^ aspect ratio calculation ^

        sceneParameters.mesh = mesh;
        sceneParameters.shader = m_sceneShader.get();
        sceneParameters.model = transform.getModelMatrix();
        sceneParameters.view = view;
        sceneParameters.projection = projection;
        sceneParameters.viewPos = camPos;

        if (mainLightExists) {
            Light& light = lightPool.m_componentData[lightIndex];
            sceneParameters.light.position = light.position;
            sceneParameters.light.color = light.color;
            sceneParameters.light.direction = light.direction;
            sceneParameters.light.intensity = light.intensity;
        } else {
                sceneParameters.light.position = glm::vec3(5.0f, 10.0f, 5.0f);
                sceneParameters.light.color = glm::vec3(1.0f, 1.0f, 1.0f);      
                sceneParameters.light.direction = glm::vec3(-0.2f, -1.0f, -0.3f); 
                sceneParameters.light.intensity = 1.0f;
        };

        m_Renderer.Submit(sceneParameters);
    }
}