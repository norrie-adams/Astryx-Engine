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

#include "Application.h"
#include "asset/ModelLoader.h"
#include "core/Input.h"
#include "core/Log.h"
#include "rendering/Camera.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "scene/Light.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "stats/renderer/renderer_stats.h"

// Handles mouse movement and forwards deltas to active camera
static Camera *g_Camera = nullptr;

static bool firstMouse = true;
static float lastX = 400.0f;
static float lastY = 300.0f;

// Mouse-look Function
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
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

Application::Application() {}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
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

    auto cubeData = Loader::loadModel("test_assets/engine_cube.obj");
    std::vector<float> cubeVertices = Loader::buildMeshData(cubeData);

    auto planeData = Loader::loadModel("test_assets/engine_plane.obj");
    std::vector<float> planeVertices = Loader::buildMeshData(planeData);

    Log::info("Loaded " + std::to_string(cubeData.vertices.size()) + " vertices");
    Log::info("Loaded " + std::to_string(cubeData.faces.size()) + " faces");

    Log::info("Loaded " + std::to_string(planeData.vertices.size()) + " vertices");
    Log::info("Loaded " + std::to_string(planeData.faces.size()) + " faces");

    m_Shader = std::make_unique<Shader>("assets/shaders/blinn_phong.vert", "assets/shaders/blinn_phong.frag");
    m_shadowShader = std::make_unique<Shader>("assets/shaders/shadow_map.vert", "assets/shaders/shadow_map.frag");

    m_Shader->use();
    m_Shader->setInt("diffuseTexture", 0);
    m_Shader->setInt("shadowMap", 1);

    m_Cube = std::make_unique<GameObject>(cubeVertices.data(), cubeVertices.size());
    m_Cube->transform.position = glm::vec3(-2.0f, 0.0f, -5.0f);

    m_Cube2 = std::make_unique<GameObject>(cubeVertices.data(), cubeVertices.size());
    m_Cube2->transform.position = glm::vec3(2.0f, 0.0f, -5.0f);

    m_Cube3 = std::make_unique<GameObject>(cubeVertices.data(), cubeVertices.size());
    m_Cube3->transform.position = glm::vec3(6.0f, 0.0f, -5.0f);

    m_Plane = std::make_unique<GameObject>(planeVertices.data(), planeVertices.size());
    m_Plane->transform.position = glm::vec3(0.0f, -1.0f, -5.0f);

    m_Texture = std::make_unique<Texture>("test_assets/brick_texture_test.jpg");

    // Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true); 
    ImGui_ImplOpenGL3_Init("#version 330");       

    return true;
}

// Renders a single frame (forward rendering pass)
void Application::render()
{
    rendererStats.drawCalls = 0;
    Light light;

    light.position = glm::vec3(20.0f, 20.0f, 20.0f);
    light.color = glm::vec3(1.0f);
    light.direction = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));
    light.intensity = 1.0f;

    if (m_Cube2)
    {
        m_Cube->transform.rotation.y = 90.0f * m_DeltaTime;
    } 

   /*  if (m_Plane)
    {
        m_Plane->transform.rotation.x = -90.0f;
    } */

    // -------------------------------------
    //               PASS 1 
    // -------------------------------------

    m_Renderer.BeginShadowPass(light, *m_shadowShader);

    if (m_Cube)
    {
        glm::mat4 model1 = m_Cube->transform.getModelMatrix();
        m_Renderer.SubmitShadow(*m_shadowShader, model1, *m_Cube);
    }

    if (m_Cube2)
    {
        glm::mat4 model2 = m_Cube2->transform.getModelMatrix();
        m_Renderer.SubmitShadow(*m_shadowShader, model2, *m_Cube2);
    }

    if (m_Cube3)
    {
        glm::mat4 model3 = m_Cube3->transform.getModelMatrix();
        m_Renderer.SubmitShadow(*m_shadowShader, model3, *m_Cube3);
    }

    m_Renderer.EndShadowPass();

    // ---------------------------------
    //              PASS 2
    // ---------------------------------

    m_Renderer.BeginScenePass(*m_Shader, m_FramebufferWidth, m_FramebufferHeight);

    float aspect = (float)m_FramebufferWidth / (float)m_FramebufferHeight;

    glm::mat4 view = m_Camera.getViewMatrix();                                          // View transform (camera space)
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f); // Perspective projection
    glm::vec3 camPos = m_Camera.getPosition();

    if (m_Texture)
    {
        m_Texture->bind();
    }

    m_Renderer.BindShadowMap(*m_Shader);

    if (m_Plane) {
        glm::mat4 planeModel = m_Plane->transform.getModelMatrix();
        m_Renderer.Submit(*m_Plane, *m_Shader, light, planeModel, view, projection, camPos);
    }
    if (m_Cube) {
        glm::mat4 model1 = m_Cube->transform.getModelMatrix();
        m_Renderer.Submit(*m_Cube, *m_Shader, light, model1, view, projection, camPos);
    }
    if (m_Cube2) {
        m_Cube2->transform.rotation.y += 90.0f * m_DeltaTime;
        glm::mat4 model2 = m_Cube2->transform.getModelMatrix();
        m_Renderer.Submit(*m_Cube2, *m_Shader, light, model2, view, projection, camPos);
    }
    if (m_Cube3) {
        glm::mat4 model3 = m_Cube3->transform.getModelMatrix();
        m_Renderer.Submit(*m_Cube3, *m_Shader, light, model3, view, projection, camPos);
    }
}

void Application::renderImGui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Will be moved to another file later, just temporary
    {
        float padding = 10.0f; // Distance from the screen edges
        ImGui::SetNextWindowPos(ImVec2(padding, padding), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(340, 120), ImGuiCond_Always);

        ImGui::Begin("Astryx Engine Debug Panel");
        
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
                    1000.0f / ImGui::GetIO().Framerate, 
                    ImGui::GetIO().Framerate);

        ImGui::Text("Application Draw Calls (Per Frame): %u", 
                    rendererStats.drawCalls);
                    
        ImGui::Separator();
        
        const GLubyte* renderAPIVersion = glGetString(GL_VERSION);
        ImGui::Text("OpenGL: %s",
            reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        ImGui::Text("GPU: %s",
            reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

        ImGui::Text("Vendor: %s",
            reinterpret_cast<const char*>(glGetString(GL_VENDOR)));

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

        renderImGui();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}