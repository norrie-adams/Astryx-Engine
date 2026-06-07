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
#include "core/Input.h"
#include "assest/ModelLoader.h"

// Vertex shader
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
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


Camera camera; 
bool firstMouse = true;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

int main()
{
    Log::info("Engine initialized");

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

    Input::init(window);
    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    auto modelData = Loader::loadModel("test_assets/engine_model.obj");
    std::vector<float> openGLVertices = Loader::buildMeshData(modelData);

    Log::info("Loaded " + std::to_string(modelData.vertices.size()) + " vertices");
    Log::info("Loaded " + std::to_string(modelData.faces.size()) + " faces");

    Shader shader(vertexShaderSource, fragmentShaderSource);
    
    GameObject cube(openGLVertices.data(), openGLVertices.size());

    float lastFrame = 0.0f;

    // Set cursor modes and callbacks
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback); 

    // MAIN LOOP
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // INPUT
        camera.processInput(deltaTime);

        // RENDER
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Model Matrix
        glm::mat4 model = glm::mat4(1.0f);
        float angle = glfwGetTime() * 2.0f;
        model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));

        // View Matrix
        glm::mat4 view = camera.getViewMatrix();

        // Projection Matrix
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        cube.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}