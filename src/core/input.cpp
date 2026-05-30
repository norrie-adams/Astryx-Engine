#include "Input.h"

std::bitset<GLFW_KEY_LAST + 1> Input::m_KeyStates;

void Input::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, Input::keyCallback);
    m_KeyStates.reset();
}

bool Input::isKeyPressed(int keycode) {
    if (keycode < 0 || keycode > GLFW_KEY_LAST) return false;
    
    return m_KeyStates.test(keycode);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key < 0 || key > GLFW_KEY_LAST) return;

    if (action == GLFW_PRESS) {
        m_KeyStates.set(key, true);
    } 
    else if (action == GLFW_RELEASE) {
        m_KeyStates.set(key, false);
    }
}
