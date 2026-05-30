#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Input
{
public: 
    static void init(GLFWwindow* window);

    static bool isWPressed();

private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static bool m_IsWPressed;
};

