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

#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "scene/GameObject.h"
#include "core/Log.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

void Renderer::CreateShadowMap() {
    glGenFramebuffers(1, &m_depthMapFBO);

    glGenTextures(1, &m_depthMap);
    glBindTexture(GL_TEXTURE_2D, m_depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_SHADOW_WIDTH, m_SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::Init() { 
    glEnable(GL_DEPTH_TEST); 
    CreateShadowMap();
}

void Renderer::BeginShadowPass(Light &light, Shader &shader) {
    // Light Space Matrix Calculation
    float near_plane = 1.0f, far_plane = 60.0f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(light.position, glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3( 0.0f, 1.0f, 0.0f));
    m_lightSpaceMatrix = lightProjection * lightView;

    glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
    glViewport(0, 0, m_SHADOW_WIDTH, m_SHADOW_HEIGHT);
    glClear(GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setMat4("m_lightSpaceMatrix", m_lightSpaceMatrix);
}

void Renderer::SubmitShadow(ShadowPassParameters shadowPassParameters) {
    shadowPassParameters.shadowShader->setMat4("model", shadowPassParameters.model);
    shadowPassParameters.mesh->draw();
}

void Renderer::EndShadowPass() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::BindShadowMap(Shader &shader) {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_depthMap);
    shader.setInt("shadowMap", 1);
}

void Renderer::BeginScenePass(Shader &shader, int screenWidth, int screenHeight) {
    glViewport(0, 0, screenWidth, screenHeight);
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader.use();
    shader.setMat4("m_lightSpaceMatrix", m_lightSpaceMatrix);
    BindShadowMap(shader);
}

void Renderer::Submit(MainPassParameters mainPassParameters) {
    mainPassParameters.shader->use(); 
    mainPassParameters.shader->setInt("diffuseTexture", 0);
    mainPassParameters.shader->setInt("shadowMap", 1);

    // Texture   
    if (mainPassParameters.texture != nullptr) {
        mainPassParameters.texture->bind();
        mainPassParameters.shader->setBool("useTexture", true);
    } else {
        // Unbinded so slot is empty
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        mainPassParameters.shader->setBool("useTexture", false);
        mainPassParameters.shader->setVec3("fallbackColor", glm::vec3(0.7, 0.7, 0.7));
    }

    mainPassParameters.shader->setMat4("model", mainPassParameters.model);
    mainPassParameters.shader->setMat4("view", mainPassParameters.view);
    mainPassParameters.shader->setMat4("projection", mainPassParameters.projection);
    mainPassParameters.shader->setVec3("viewPos", mainPassParameters.viewPos);
    
    mainPassParameters.shader->setMat4("m_lightSpaceMatrix", m_lightSpaceMatrix);

    mainPassParameters.shader->setVec3("light.position", mainPassParameters.light.position);
    mainPassParameters.shader->setVec3("light.color", mainPassParameters.light.color);
    mainPassParameters.shader->setVec3("light.direction",mainPassParameters.light.direction);
    mainPassParameters.shader->setFloat("light.intensity", mainPassParameters.light.intensity);
    
    mainPassParameters.mesh->draw();
}
