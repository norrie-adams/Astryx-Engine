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

/* 
Future Rendering Functions

void RenderShadowPass(); 
{
    
}

void RenderScenePass();
{

} 

*/

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