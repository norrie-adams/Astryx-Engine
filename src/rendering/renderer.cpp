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
#include "scene/GameObject.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

void Renderer::CreateShadowMap() {
    glGenFramebuffers(1, &m_depthMapFBO);

    glGenTextures(1, &m_depthMap);
    glBindTexture(GL_TEXTURE_2D, m_depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_SHADOW_WIDTH, m_SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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

void Renderer::BeginShadowPass(Shader &shader, Light &light) {
    // Light Space Matrix Calculation
    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(light.position, light.position + light.direction, glm::vec3( 0.0f, 1.0f, 0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
    glViewport(0, 0, m_SHADOW_WIDTH, m_SHADOW_HEIGHT);
    glClear(GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setMat4("m_lightSpaceMatrix", m_lightSpaceMatrix);
}

void Renderer::SubmitShadow(Shader &shader, GameObject &gameObject, glm::mat4 &model) {
    shader.setMat4("model", model);
    gameObject.draw(shader);
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

void Renderer::Submit(GameObject &gameObject, Shader &shader, Light &light, const glm::mat4 &model, const glm::mat4 &view,
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

    shader.setMat4("m_lightSpaceMatrix", m_lightSpaceMatrix);

    shader.setVec3("light.position", light.position);
    shader.setVec3("light.color", light.color);
    shader.setFloat("light.intensity", light.intensity);
    shader.setVec3("lightColor", glm::vec3(1.0f));
    shader.setVec3("viewPos", viewPos);

    gameObject.draw(shader);
}
