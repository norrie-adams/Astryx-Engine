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

    void BeginShadowPass(const Light &light, Shader &shader, GameObject &gameObject, glm::mat4 model);
    void SubmitShadow(Shader &shader, glm::mat4 &model, GameObject &gameObject);
    void BindShadowMap(Shader &shader);
    void BeginScenePass();
    void Submit(GameObject &obj, Shader &shader, const glm::mat4 &model, const glm::mat4 &view,
                const glm::mat4 &projection, const glm::vec3 &viewPos);

    void SetLight(const Light& light, Shader &shader);

private:
    GLuint m_depthTexture;
    GLuint m_shadowFBO;

    glm::mat4 m_lightSpaceMatrix;
};