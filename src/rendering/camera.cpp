// Camera
// Handles view position and orientation for the scene camera.
//
// Controls (v0.1):
// - W/S: move forward/backward along view direction
// - A/D: strafe left/right
// - Mouse: rotates camera (yaw + pitch)
//
// Notes:
// - Uses yaw/pitch Euler angles to build direction vector
// - Pitch is clamped to prevent flipping at extreme angles
// - Generates view matrix using glm::lookAt
// - Movement is frame-rate independent using deltaTime

#include "Camera.h"
#include "core/Input.h"
#include <glm/gtc/matrix_transform.hpp>

// Starting Camera Position
Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;
    // NOTE: unused in v0.1 (reserved for future rotation mode)
    rotationSpeed = 50.0f;
    mouseSensitivity = 0.1f;

    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() { return glm::lookAt(position, position + front, up); }

// Polls input and applies transform
void Camera::processInput(float deltaTime)
{
    float speed = 2.0f * deltaTime;
    if (Input::isKeyPressed(GLFW_KEY_W))
        position += front * speed;
    if (Input::isKeyPressed(GLFW_KEY_S))
        position -= front * speed;

    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
    if (Input::isKeyPressed(GLFW_KEY_A))
        position -= right * speed;
    if (Input::isKeyPressed(GLFW_KEY_D))
        position += right * speed;
}

// Applies WASD movement based on current input state
void Camera::processMouseMovement(float xoffset, float yoffset)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Prevents camera flip when looking straight up/down (avoids gimbal lock)
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

// Build direction vector from yaw/pitch (spherical coordinates)
void Camera::updateCameraVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}