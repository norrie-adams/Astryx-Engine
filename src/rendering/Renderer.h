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
    
    void CreateShadowMap();

    // Pass 1
    void BeginShadowPass(const Light &light, Shader &shader);
    void SubmitShadow(Shader &shader, glm::mat4 &model, GameObject &gameObject);
    void BindShadowMap(Shader &shader);

    // Pass 2
    void BeginScenePass(Shader &mainShader, int screenWidth, int screenHeight);
    void Submit(GameObject &obj, Shader &shader, const glm::mat4 &model, const glm::mat4 &view,
                const glm::mat4 &projection, const glm::vec3 &viewPos, const Light &light);

private:
    GLuint m_depthTexture;
    GLuint m_shadowFBO;

    glm::mat4 m_lightSpaceMatrix;
};