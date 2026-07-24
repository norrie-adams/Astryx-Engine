#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "scene/Light.h"

class GameObject;
class Shader;

class Renderer
{
public:
    void Init();

    void BeginFrame();
    
    void CreateShadowMap();

    void Submit(GameObject &obj, Shader &shader, const glm::mat4 &model, const glm::mat4 &view,
                const glm::mat4 &projection, const glm::vec3 &viewPos);

    void RenderShadowPass(const Light &light, Shader &shader, GameObject &gameObject, glm::mat4 model);
    void RenderScenePass();

    void SetLight(const Light& light, Shader &shader);

private:
    GLuint m_depthTexture;
    GLuint m_shadowFBO;

};