#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "rendering/Shader.h"
#include "rendering/Mesh.h"
#include "scene/GameObject.h"
#include "core/Log.h"

// Vertex shader
const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec3 uPos;

void main()
{
    gl_Position = vec4(aPos + uPos, 1.0);
}
)";

// Fragment shader
const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.4, 0.6, 0.2, 1.0);
}
)";

int main()
{
    Log::info("Engine initalized");

    // GLFW init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Astryx Engine", NULL, NULL);
    if (!window)
    {
        Log::error("GLFW Init Failed");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // GLAD init
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::error("GLAD Init Failed");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    // Triangle data
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,

     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
    };

    // Shader + object
    Shader shader(vertexShaderSource, fragmentShaderSource);
    GameObject triangle(vertices, sizeof(vertices) / sizeof(float));

    // INPUT SPEED
    float lastFrame = 0.0f;

    // MAIN LOOP
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float speed = 2.0f * deltaTime;

        // INPUT 
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            triangle.transform.x += speed;

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            triangle.transform.x -= speed;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            triangle.transform.y += speed;

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            triangle.transform.y -= speed;

        // RENDER
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        triangle.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}