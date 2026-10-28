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
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "stats/renderer/RendererStats.h"
#include "ecs/Registry.h"
#include "asset/AssetManager.h"

// Globals
std::shared_ptr<Registry> g_Registry = nullptr;
std::shared_ptr<AssetManager> g_AssetManager = nullptr;

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
        Log::error("Failed to initialize GLAD");
        return false;
    }

    Input::init(m_Window);

    g_Camera = &m_Camera;

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_Window, mouse_callback);

    glViewport(0, 0, 800, 600);
    m_Renderer.Init();

    g_Registry = std::make_shared<Registry>();
    g_AssetManager = std::make_shared<AssetManager>();
    m_renderSystem = std::make_unique<RenderSystem>(g_Registry, *g_AssetManager);

    g_AssetManager->init(g_Registry);

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
        // Deltatime
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
        m_DeltaTime = deltaTime;

        glfwGetFramebufferSize(m_Window, &m_FramebufferWidth, &m_FramebufferHeight);
        glViewport(0, 0, m_FramebufferWidth, m_FramebufferHeight);

        // INPUT
        m_Camera.processInput(deltaTime);

        // Render
        m_renderSystem->render(m_Renderer, m_FramebufferWidth, m_FramebufferHeight);

        renderImGui();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}