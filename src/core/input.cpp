#include "Input.h"

bool Input::m_IsWPressed = false;

void Input::init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, keyCallback);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W)
    {
        if (action == GLFW_PRESS)
            m_IsWPressed = true;
        else if (action == GLFW_RELEASE)
            m_IsWPressed = false;
    }
}

bool Input::isWPressed()
{
    return m_IsWPressed;
}