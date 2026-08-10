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

    void BeginShadowPass(Light &light, Shader &shader);

    void SubmitShadow(Shader &shader, glm::mat4 &model, GameObject &gameObject);

    void EndShadowPass();

    void BindShadowMap(Shader &shader);

    void BeginScenePass(Shader &shader, int screenWidth, int screenHeight);

    void Submit(GameObject &gameObject, Shader &shader, Light &light, const glm::mat4 &model, const glm::mat4 &view,
                      const glm::mat4 &projection, const glm::vec3 &viewPos);

    void SetLight(const Light &light, Shader &shader);

private:
    GLuint m_depthMapFBO;
    GLuint m_depthMap;

    glm::mat4 m_lightSpaceMatrix;

    const unsigned int m_SHADOW_WIDTH = 2048, m_SHADOW_HEIGHT = 2048;
};