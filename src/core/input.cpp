// Input 
//
// Simple keyboard input system using GLFW callbacks.
//
// Design:
// - Stores key states as a boolean bitset (pressed / not pressed)
// - Updated via GLFW key callback
// - Queried anywhere in the engine via isKeyPressed()
//
// Behavior:
// - True when key is currently held down
// - False when key is released
// - No distinction between "pressed this frame" or "held"
//
// Notes:
// - Keyboard only (no mouse input yet)
// - State is event-updated via GLFW, not manually polled

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
