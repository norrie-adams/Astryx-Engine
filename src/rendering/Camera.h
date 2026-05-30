#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    Camera();

    glm::mat4 getViewMatrix();
};