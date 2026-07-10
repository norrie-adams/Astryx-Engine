#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bitset>

class Input
{
public:
    static void init(GLFWwindow *window);
    static bool isKeyPressed(int keycode);
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
    static std::bitset<GLFW_KEY_LAST + 1> m_KeyStates;
};
