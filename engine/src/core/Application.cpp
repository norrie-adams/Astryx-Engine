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

#include "core/Application.hpp"
#include "asset/ModelLoader.hpp"
#include "core/Input.hpp"
#include "core/Log.hpp"
#include "rendering/Camera.hpp"
#include "rendering/Renderer.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ui/UIManager.hpp"
#include "scene/Registry.hpp"
#include "asset/AssetManager.hpp"

// Globals
std::shared_ptr<Registry> g_Registry = nullptr;
std::shared_ptr<AssetManager> g_AssetManager = nullptr;

// Handles mouse movement and forwards deltas to active camera

static bool firstMouse = true;
static bool isMenuOpen = false;
static float lastX = 400.0f;
static float lastY = 300.0f;

// Mouse-look Function
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    ImGui_ImplGlfw_CursorPosCallback(window, xposIn, yposIn);
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if(!camera) {
        Log::Error("Camera is null, so you can't look around! Its okay you can just mess around with the UI its interesting enough...");
    }

    if (camera && camera->isMenuOpen()) {
        firstMouse = true;
        return;
    }

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

    if (camera)
    {
        camera->processMouseMovement(xoffset, yoffset);
    }
}

void Application::toggleInputMode(GLFWwindow* window) {
    ImGuiIO& io = ImGui::GetIO();
    if (g_Camera->isMenuOpen()) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // UI
        io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Game
        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
    };
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
        Log::Fatal("GLFW Init Failed");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(800, 600, "Astryx Engine", NULL, NULL);
    if (!m_Window)
    {
        Log::Fatal("Window Creation Failed");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    // GLAD init
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::Fatal("Failed to initialize GLAD");
        return false;
    }

    g_Registry = std::make_shared<Registry>();
    g_AssetManager = std::make_shared<AssetManager>();
    g_Camera = std::make_unique<Camera>();
    glfwSetWindowUserPointer(m_Window, g_Camera.get());

    Input::init(m_Window);
    // Sets keybinds since ImGui doesn't do it for us
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* w, int b, int a, int m) { ImGui_ImplGlfw_MouseButtonCallback(w, b, a, m); });
    glfwSetScrollCallback(m_Window, [](GLFWwindow* w, double x, double y) { ImGui_ImplGlfw_ScrollCallback(w, x, y); });
    glfwSetKeyCallback(m_Window, [](GLFWwindow* w, int k, int s, int a, int m) { ImGui_ImplGlfw_KeyCallback(w, k, s, a, m); });
    glfwSetCharCallback(m_Window, [](GLFWwindow* w, unsigned int c) { ImGui_ImplGlfw_CharCallback(w, c); });
    
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_Window, ::mouse_callback);

    // Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init("#version 330");  
    // Install ImGui callbacks after the engine callbacks so it chains to them.
    ImGui_ImplGlfw_InitForOpenGL(m_Window, false);

    glViewport(0, 0, 800, 600);
    m_Renderer.Init();
    m_uiManager = std::make_unique<UIManager>(g_Registry);
    m_renderSystem = std::make_unique<RenderSystem>(g_Registry, *g_AssetManager, *g_Camera);
    g_AssetManager->init(g_Registry);  

    return true;
}

void Application::renderUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_uiManager->drawUI();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Main engine loop (runs until window close)
// Handles timing, input, updates, and rendering
void Application::run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        // Time
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
        m_DeltaTime = deltaTime;

        glfwGetFramebufferSize(m_Window, &m_FramebufferWidth, &m_FramebufferHeight);
        glViewport(0, 0, m_FramebufferWidth, m_FramebufferHeight);

        // Input
        g_Camera->processInput(m_Window, deltaTime);
        toggleInputMode(m_Window);

        // Render
        m_renderSystem->render(m_Renderer, m_FramebufferWidth, m_FramebufferHeight);

        // UI
        renderUI();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}