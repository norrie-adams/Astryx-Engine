#pragma once

// Graphics & Windowing
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM Math
#define GLM_ENABLE_EXPERIMENTAL

// Engine Systems
#include "rendering/Camera.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/RenderSystem.hpp"
#include "ui/UIManager.hpp"

// Standard Library
#include <memory>

class Application
{
public:
    ~Application();
    Application();

    void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
    bool init();
    void run();
    std::shared_ptr<Registry> getRegistry() const { return g_Registry; }
    void toggleInputMode(GLFWwindow* window);

private:
    void renderUI();

    GLFWwindow *m_Window = nullptr;
    const unsigned int m_Width = 800;
    const unsigned int m_Height = 600;

    std::unique_ptr<Camera> g_Camera;
    std::unique_ptr<UIManager> m_uiManager;
    std::unique_ptr<RenderSystem> m_renderSystem;
    Renderer m_Renderer;

    int m_FramebufferWidth = 800;
    int m_FramebufferHeight = 600;

    // Timing
    float m_LastFrame = 0.0f;
    float m_DeltaTime = 0.0f;
};