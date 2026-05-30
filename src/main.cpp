#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>                  
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>          

#include "rendering/Shader.h"
#include "rendering/Mesh.h"
#include "scene/GameObject.h"
#include "core/Log.h"
#include "rendering/Camera.h"

// Vertex shader
const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position =
        projection *
        view *
        model *
        vec4(aPos, 1.0);
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
    // Back face
    -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,

    // Front face
    -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,

    // Left face
    -0.5f,  0.5f,  0.5f,  -0.5f,  0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,

    // Right face
     0.5f,  0.5f,  0.5f,   0.5f,  0.5f, -0.5f,   0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,

    // Bottom face
    -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,  -0.5f, -0.5f, -0.5f,

    // Top face
    -0.5f,  0.5f, -0.5f,   0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,  -0.5f,  0.5f, -0.5f,
    };

    // Shader + object
    Shader shader(vertexShaderSource, fragmentShaderSource);
    GameObject triangle(vertices, sizeof(vertices) / sizeof(float));

    // INPUT SPEED
    float lastFrame = 0.0f;

    Camera camera;

    // MAIN LOOP
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float speed = 2.0f * deltaTime;

        // INPUT 
        // INPUT 
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.position += camera.front * speed;

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.position -= camera.front * speed; 

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.position -= glm::normalize(glm::cross(camera.front, camera.up)) * speed;

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.position += glm::normalize(glm::cross(camera.front, camera.up)) * speed; 

        // RENDER
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Model Matrix
        glm::mat4 model = glm::mat4(1.0f);

        float angle = glfwGetTime() * 2.0f;

        model = glm::rotate(
            model,
            angle,
            glm::vec3(0.5f, 1.0f, 0.0f)
        );

        // View Matrix
        glm::mat4 view = camera.getViewMatrix();

        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            800.0f / 600.0f,
            0.1f,
            100.0f
        );

        shader.use();

        glUniformMatrix4fv(
            glGetUniformLocation(shader.ID, "model"),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(shader.ID, "view"),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(shader.ID, "projection"),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        triangle.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}