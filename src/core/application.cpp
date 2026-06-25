// Application 
//
// Core engine runtime responsible for:
// - Initializing GLFW + OpenGL context (GLAD)
// - Creating window and managing lifecycle
// - Driving the main engine loop
// - Managing input, camera, renderer, and assets
//
// Frame execution order:
// 1. Compute deltaTime
// 2. Update viewport size
// 3. Process camera input
// 4. Render scene
// 5. Swap buffers
// 6. Poll events
//
// Notes:
// - Mouse input handled via GLFW callbacks
// - Camera is updated directly from input
// - Forward rendering only (no ECS, no batching yet)
// - Temporary global camera pointer used for mouse callback routing

#include <iostream>
#include "Application.h"
#include "core/Log.h"
#include "core/Input.h"
#include "asset/ModelLoader.h"
#include "rendering/Camera.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"

// Handles mouse movement and forwards deltas to active camera
static Camera* g_Camera = nullptr;

static bool firstMouse = true;
static float lastX = 400.0f;
static float lastY = 300.0f;

// Mouse-look Function
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (g_Camera)
    {
        g_Camera->processMouseMovement(xoffset, yoffset);
    }
}

Application::Application() 
{ 
}

Application::~Application() 
{
    if (m_Window) 
    {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }

    glfwTerminate();
}

// Initializes GLFW, OpenGL context, input system, renderer, and assets
bool Application::init() 
{
    if (!glfwInit())
    {
        Log::error("GLFW Init Failed");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(800, 600, "Astryx Engine", NULL, NULL);
    if (!m_Window)
    {
        Log::error("GLFW Window Creation Failed");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    // GLAD init
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::error("GLAD Init Failed");
        return false;
    }

    Input::init(m_Window);

    g_Camera = &m_Camera;

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_Window, mouse_callback);

    glViewport(0, 0, 800, 600);
    m_Renderer.Init();

    auto modelData = Loader::loadModel("test_assets/engine_cube_triangulated.obj");
    std::vector<float> openGLVertices = Loader::buildMeshData(modelData);

    Log::info("Loaded " + std::to_string(modelData.vertices.size()) + " vertices");
    Log::info("Loaded " + std::to_string(modelData.faces.size()) + " faces");

    m_Shader = std::make_unique<Shader>("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    m_Cube = std::make_unique<GameObject>(openGLVertices.data(), openGLVertices.size());
    m_Cube->transform.position = glm::vec3(-2.0f, 0.0f, -5.0f);

    m_Cube2 = std::make_unique<GameObject>(openGLVertices.data(), openGLVertices.size());
    m_Cube2->transform.position = glm::vec3(2.0f, 0.0f, -5.0f);

    m_Cube3 = std::make_unique<GameObject>(openGLVertices.data(), openGLVertices.size());
    m_Cube3->transform.position = glm::vec3(6.0f, 0.0f, -5.0f);

    m_Texture = std::make_unique<Texture>("test_assets/brick_texture_test.jpg");
    
    return true;
}

// Renders a single frame (forward rendering pass)
void Application::render() 
{
    m_Renderer.BeginFrame();

    float aspect = (float)m_FramebufferWidth / (float)m_FramebufferHeight;

    glm::mat4 view = m_Camera.getViewMatrix(); // View transform (camera space)
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f); // Perspective projection

    if (m_Texture) 
    {
        m_Texture->bind();
    }

    if (m_Cube) 
    {
        glm::mat4 model1 = m_Cube->transform.getModelMatrix();
        m_Renderer.Submit(*m_Cube, *m_Shader, model1, view, projection);
    }

    if (m_Cube2) 
    {
        m_Cube2->transform.rotation.y += 90.0f * m_DeltaTime;
        glm::mat4 model2 = m_Cube2->transform.getModelMatrix();
        m_Renderer.Submit(*m_Cube2, *m_Shader, model2, view, projection);
    }

    if (m_Cube3) 
    {
        glm::mat4 model3 = m_Cube3->transform.getModelMatrix();
        m_Renderer.Submit(*m_Cube3, *m_Shader, model3, view, projection);
        m_Cube3->transform.rotation.z += 700.0f * m_DeltaTime;
    }
}

// Main engine loop (runs until window close)
// Handles timing, input, updates, and rendering
void Application::run() 
{
    while (!glfwWindowShouldClose(m_Window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
        m_DeltaTime = deltaTime;

        glfwGetFramebufferSize(m_Window, &m_FramebufferWidth, &m_FramebufferHeight);
        glViewport(0, 0, m_FramebufferWidth, m_FramebufferHeight);

        // INPUT
        m_Camera.processInput(deltaTime);

        render();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}