#include "ui/UIManager.hpp"
#include "imgui.h"
#include "stats/renderer/RendererStats.hpp"
#include "glad/glad.h"

void UIManager::drawDebugPanel() {
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
