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

void Renderer::Init() { glEnable(GL_DEPTH_TEST); }

void Renderer::BeginFrame()
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Submit(GameObject &obj, Shader &shader, const glm::mat4 &model, const glm::mat4 &view,
                      const glm::mat4 &projection, const glm::vec3 &viewPos)
{
    shader.use();

    // Matrix uniforms
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3f(shader.getUniform("lightPos"), viewPos.x, viewPos.y, viewPos.z); 
    glUniform3f(shader.getUniform("lightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(shader.getUniform("viewPos"), viewPos.x, viewPos.y, viewPos.z);
    obj.draw(shader);
}