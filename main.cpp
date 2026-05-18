#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Mesh.h"

// Vertex shader
const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec3 uPos;

void main()
{
    gl_Position = vec4(aPos + uPos, 1.0);
})";

// Fragment shader
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.4, 0.6, 0.2, 1.0);
}
)";

struct Transform {
    float x = 0;
    float y = 0;
    float z = 0;
};

class GameObject {
    public:
        Mesh mesh;
        Transform transform;

        GameObject(float* vertices, unsigned int size)
            : mesh(vertices, size) {}

        void draw(Shader& shader) {

            glUniform3f(
                shader.getUniform("uPos"),
                transform.x,
                transform.y,
                transform.z
            );

            mesh.draw();
        }
};

int main()
{
    // GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Astryx Engine", NULL, NULL);
    glfwMakeContextCurrent(window);

    // GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD failed\n";
        return -1;
    }

    // TRIANGLE DATA
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // SHADER OBJECT
    Shader shader(vertexShaderSource, fragmentShaderSource);
    GameObject triangle(vertices, sizeof(vertices));

    // LOOP
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        triangle.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}