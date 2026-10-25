#pragma once
#include "ecs/Registry.h"
#include "Shader.h"
#include "Renderer.h"
#include <memory>

class RenderSystem { 
private:
    std::shared_ptr<Registry> m_Registry;
    std::unique_ptr<Shader> m_shadowShader;
    std::unique_ptr<Shader> m_sceneShader;

public:
    RenderSystem(std::shared_ptr<Registry> registry) : m_Registry(registry) {
        m_sceneShader = std::make_unique<Shader>("assets/shaders/blinn_phong.vert", "assets/shaders/blinn_phong.frag");
        m_shadowShader = std::make_unique<Shader>("assets/shaders/shadow_map.vert", "assets/shaders/shadow_map.frag");
    };
    void render(Renderer& m_Renderer, int screenWidth, int screenHeight);

};