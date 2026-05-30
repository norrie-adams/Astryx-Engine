#include "Camera.h"
#include "core/Input.h"
#include <glm/gtc/matrix_transform.hpp> 

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    front    = glm::vec3(0.0f, 0.0f, -1.0f);
    up       = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::processInput(float deltaTime)
{
    float speed = 2.0f * deltaTime;

    if (Input::isKeyPressed(GLFW_KEY_W))
        position += front * speed;

    if (Input::isKeyPressed(GLFW_KEY_S))
        position -= front * speed;

    if (Input::isKeyPressed(GLFW_KEY_A))
        position -= glm::normalize(glm::cross(front, up)) * speed;

    if (Input::isKeyPressed(GLFW_KEY_D))
        position += glm::normalize(glm::cross(front, up)) * speed;
}