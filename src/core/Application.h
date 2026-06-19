#pragma once

// Graphics & Windowing
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Engine Systems
#include "rendering/Camera.h"
#include "rendering/Shader.h"
#include "scene/GameObject.h"
#include "rendering/Renderer.h"
#include "rendering/Texture.h"

// Standard Library
#include <memory>

class Application {
public:
    Application();
    ~Application();

    bool init();
    void run();

private:
    void render();

    GLFWwindow* m_Window = nullptr;
    const unsigned int m_Width = 800;
    const unsigned int m_Height = 600;

    Camera m_Camera;
    Renderer m_Renderer;

    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<GameObject> m_Cube;
    std::unique_ptr<Texture> m_Texture;

    // Timing
    float m_LastFrame = 0.0f;
};