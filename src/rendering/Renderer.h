#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include "Mesh.h"
#include "ecs/components/Light.h"

class GameObject;
class Shader;
class Light;

class Renderer {
public:
    struct ShadowPassParameters {
        Shader* shadowShader = nullptr;
        glm::mat4 model;
        Mesh* mesh = nullptr;
    };
    struct MainPassParameters {
        Mesh* mesh = nullptr;
        Shader* shader = nullptr;
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 viewPos;
    };

    void CreateShadowMap();

    void Init();

    void BeginShadowPass(Light &light, Shader &shader);

    void SubmitShadow(ShadowPassParameters shadowPassParameters);

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