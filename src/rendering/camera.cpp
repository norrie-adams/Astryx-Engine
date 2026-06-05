#include "Camera.h"
#include "core/Input.h"
#include <glm/gtc/matrix_transform.hpp> 

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    front    = glm::vec3(0.0f, 0.0f, -1.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;
    rotationSpeed = 50.0f;
    mouseSensitivity = 0.1f;

    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::processInput(float deltaTime)
{
    float speed = 2.0f * deltaTime;
    if (Input::isKeyPressed(GLFW_KEY_W)) position += front * speed;
    if (Input::isKeyPressed(GLFW_KEY_S)) position -= front * speed;

    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
    if (Input::isKeyPressed(GLFW_KEY_A)) position -= right * speed;
    if (Input::isKeyPressed(GLFW_KEY_D)) position += right * speed;
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}