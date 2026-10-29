#pragma once
#include "ecs/Registry.h"
#include "ecs/System.h"
#include "asset/AssetManager.h"
#include "Camera.h"
#include "Shader.h"
#include "Renderer.h"
#include <memory>

class RenderSystem : System { 
private:
    AssetManager &m_AssetManager;
    Camera &m_Camera;
    std::unique_ptr<Shader> m_shadowShader;
    std::unique_ptr<Shader> m_sceneShader;

public:
    RenderSystem(std::shared_ptr<Registry> registry, AssetManager& assetManager, Camera& camera)
        : System(registry), m_AssetManager(assetManager), m_Camera(camera) {
        m_sceneShader = std::make_unique<Shader>("assets/shaders/blinn_phong.vert", "assets/shaders/blinn_phong.frag");
        m_shadowShader = std::make_unique<Shader>("assets/shaders/shadow_map.vert", "assets/shaders/shadow_map.frag");
    };
    void render(Renderer& m_Renderer, int screenWidth, int screenHeight);

};