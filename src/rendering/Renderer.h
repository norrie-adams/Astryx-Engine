#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "scene/Light.h"

class GameObject;
class Shader;
class Light;

class Renderer
{
public:
    void CreateShadowMap();

    void Init();

    void BeginShadowPass(Shader &shader);

    void Renderer::SubmitShadow(Shader &shader, GameObject &gameObject, glm::mat4 &model);

    void Submit(GameObject &obj, Shader &shader, const glm::mat4 &model, const glm::mat4 &view,
                      const glm::mat4 &projection, const glm::vec3 &viewPos);

    void SetLight(const Light &light, Shader &shader);

private:
    GLuint m_depthMapFBO;
    GLuint m_depthMap;

    glm::mat4 m_lightSpaceMatrix;

    const unsigned int m_SHADOW_WIDTH = 1024, m_SHADOW_HEIGHT = 1024;
};