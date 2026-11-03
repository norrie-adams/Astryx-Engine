#pragma once
#include "scene/Registry.hpp"
#include "ecs/System.hpp"
#include "asset/AssetManager.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
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
        m_sceneShader = std::make_unique<Shader>("assets/shaders/main.vert", "assets/shaders/main.frag");
        m_shadowShader = std::make_unique<Shader>("assets/shaders/shadow_map.vert", "assets/shaders/shadow_map.frag");
    };
    void render(Renderer& m_Renderer, int screenWidth, int screenHeight);

};