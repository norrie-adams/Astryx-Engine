#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera();

    glm::mat4 getViewMatrix();

    void processInput(GLFWwindow* window, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);

    glm::vec3 getPosition() const { return position; } 
    bool isMenuOpen() { return m_isMenuOpen; }

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float rotationSpeed;
    float mouseSensitivity;

    bool m_isMenuOpen = false;
    bool m_TabPressedLastFrame = false;

    void updateCameraVectors();
};