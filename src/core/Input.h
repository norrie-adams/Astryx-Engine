#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bitset> // Replaced <unordered_map>

class Input {
public:
    static void init(GLFWwindow* window);
    static bool isKeyPressed(int keycode);

private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    static std::bitset<GLFW_KEY_LAST + 1> m_KeyStates;
};
