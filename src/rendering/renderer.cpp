// Renderer
//
// Handles the basic forward rendering pipeline:
// - Enables depth testing
// - Clears frame buffers each frame
// - Issues draw calls with MVP matrices
//
// Sigle-pass Renderer
// Camera/view logic is external and passed in per frame
// Each Submit() represents one draw call

#include <glad/glad.h>
#include "Renderer.h"
#include "Shader.h"
#include "scene/GameObject.h"
#include "core/Log.h"
#include <glm/gtc/type_ptr.hpp>

void CreateShadowMap() 
{
    // Generate Depth Texture
    GLuint m_depthTexture;

    glGenTextures(1, &m_depthTexture);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    // Attach to FBO
    GLuint m_FBO;

    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        Log::error("Failed to generate framebuffer for shadows");
    }
}

void Renderer::Init() 
{ 
    glEnable(GL_DEPTH_TEST); 

    CreateShadowMap();
}

void Renderer::BeginFrame()
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderShadowPass() 
{
    
}

void RenderScenePass()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
} 

void Renderer::Submit(GameObject &obj, Shader &shader, const glm::mat4 &model, const glm::mat4 &view,
                      const glm::mat4 &projection, const glm::vec3 &viewPos)
{
    shader.use();

    // Matrix uniforms
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    shader.setVec3("lightPos", viewPos);
    shader.setVec3("lightColor", glm::vec3(1.0f));
    shader.setVec3("viewPos", viewPos);

    obj.draw(shader);
}

void Renderer::SetLight(const Light& light, Shader &shader) {
    shader.setVec3("light.position", light.position);
    shader.setVec3("light.color", light.color);
    shader.setFloat("light.intensity", light.intensity);
}