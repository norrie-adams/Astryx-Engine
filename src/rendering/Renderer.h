#pragma once

#include <glm/glm.hpp>

class GameObject;
class Shader;

class Renderer
{
public:
    void Init();

    void BeginFrame();

    void Submit(GameObject &obj, Shader &shader, const glm::mat4 &model, const glm::mat4 &view,
                const glm::mat4 &projection, const glm::vec3 &viewPos);
};