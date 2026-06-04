#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float rotationSpeed;

    Camera();

    glm::mat4 getViewMatrix();

    void processInput(float deltaTime);
    void updateCameraVectors();
};