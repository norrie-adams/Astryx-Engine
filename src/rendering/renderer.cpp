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
#include "scene/Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void Renderer::CreateShadowMap() 
{
    // Generate Depth Texture
    glGenTextures(1, &m_depthTexture);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    // Attach to FBO
    glGenFramebuffers(1, &m_shadowFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        Log::error("Failed to generate framebuffer for shadows");
    }

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
}

void Renderer::Init() 
{ 
    glEnable(GL_DEPTH_TEST); 
    CreateShadowMap();
}

void Renderer::BeginFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// -------------------------------------
//         PASS 1 (SHADOW MAPS)
// -------------------------------------

// Preperation for Pass 1
void Renderer::BeginShadowPass(const Light &light, Shader &shader, GameObject &gameObject, glm::mat4 model) 
{
    // Matrix Calculations
    glm::mat4 lightView = glm::lookAt(light.position, light.position + light.direction, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 50.0f);
    glm::mat4 m_lightSpaceMatrix = lightProjection * lightView;

    // Bind (activate) custom FBO to be used
    glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
    glViewport(0, 0, 1024, 1024);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Activates shader and passes in lightSpaceMatrix
    shader.use();
    shader.setMat4("lightSpaceMatrix", m_lightSpaceMatrix);

}

// Draws objects in Pass 1
void Renderer::SubmitShadow(Shader &shader, glm::mat4 &model, GameObject &gameObject)
{
    shader.setMat4("model", model);
    gameObject.draw(shader);
} 

// Binds depth buffer texture so the main shader can read the shadow data (positions of each object)
void Renderer::BindShadowMap(Shader &shader)
{
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    shader.setInt("shadowMap", 1);
}

void Renderer::BeginScenePass()
{
    
}

void Renderer::Submit(GameObject &gameObject, Shader &shader, const glm::mat4 &model, const glm::mat4 &view,
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

    gameObject.draw(shader);
}

void Renderer::SetLight(const Light& light, Shader &shader) {
    shader.setVec3("light.position", light.position);
    shader.setVec3("light.color", light.color);
    shader.setFloat("light.intensity", light.intensity);
}