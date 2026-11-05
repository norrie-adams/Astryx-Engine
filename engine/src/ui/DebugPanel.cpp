#include "ui/UIManager.hpp"
#include "ui/DebugPanel.hpp"
#include "imgui.h"
#include "scene/Registry.hpp"
#include "ecs/components/Components.hpp"
#include "stats/renderer/RendererStats.hpp"
#include "glad/glad.h"
#include "core/Log.hpp"
#include <string>
#include <glm/glm.hpp>

void UIManager::drawDebugPanel() {
    float padding = 10.0f; // Distance from the screen edges
    ImGui::SetNextWindowPos(ImVec2(padding, padding), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(340, 140), ImGuiCond_Always);

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


    if(ImGui::Button("Add Cube")) {
        Log::Info("Created Cube");
        uint32_t cube = m_Registry->createEntity();
        m_Registry->addComponent<Transform>(cube, Transform{
        .position = glm::vec3(xOffset, 0.0f, 0.0f),
        .rotation = glm::vec3(0.0f, 45.0f, 0.0f),
        .scale = glm::vec3(1.0f)
        });
        xOffset += 5.0f; // Increase offset of each cube
        m_Registry->addComponent<MeshRenderer>(cube, MeshRenderer{
            .modelFilePath = std::string("assets/models/engine_cube.obj")
        });
        m_Registry->addComponent<TextureComponent>(cube, TextureComponent{
            .textureFilePath = std::string("assets/textures/checkerboard.jpg")
        });
    };

    ImGui::End();
}
