#include <iostream>
#include "Application.h"
#include "core/Log.h"
#include "rendering/Camera.h"
#include "core/Input.h"
#include "asset/ModelLoader.h"
#include "rendering/Renderer.h"

// Vertex shader source
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

/// Fragment Shader Source
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.4, 0.6, 0.2, 1.0);
}
)";


// Mouse-look Variables
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
    if (m_Window) {
        glfwTerminate();
    }
}

bool Application::init() 
{
    
    // GLFW Init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(800, 600, "Astryx Engine", NULL, NULL);
    if (!m_Window)
    {
        Log::error("GLFW Init Failed");
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
    glEnable(GL_DEPTH_TEST);

    auto modelData = Loader::loadModel("test_assets/engine_model.obj");
    std::vector<float> openGLVertices = Loader::buildMeshData(modelData);

    Log::info("Loaded " + std::to_string(modelData.vertices.size()) + " vertices");
    Log::info("Loaded " + std::to_string(modelData.faces.size()) + " faces");

    m_Shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource);
    m_Cube = std::make_unique<GameObject>(openGLVertices.data(), openGLVertices.size());
    
    return true;
}

void Application::render() 
{
    m_Renderer.BeginFrame();

    // Model Matrix
    glm::mat4 model = glm::mat4(1.0f);
    float angle = glfwGetTime() * 2.0f;
    model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));

    // View Matrix
    glm::mat4 view = m_Camera.getViewMatrix();

    // Projection Matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)m_Width / m_Height, 0.1f, 100.0f);

    m_Renderer.Submit(*m_Cube, *m_Shader, model, view, projection);
}

void Application::run() 
{
    while (!glfwWindowShouldClose(m_Window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;

        // INPUT
        m_Camera.processInput(deltaTime);

        render();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}
