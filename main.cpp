#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// This code adds color to each individual pixel
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.4, 0.6, 0.2, 1.0);
}
)";

const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec2 uOffset;

void main()
{
    gl_Position = vec4(aPos + vec3(uOffset, 0.0), 1.0);
}
)";

void checkShaderCompile(unsigned int shader, const std::string& type)
{
    int success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "[SHADER COMPILE ERROR] (" << type << ")\n"
                  << infoLog << std::endl;
    }
}

void checkProgramLink(unsigned int program)
{
    int success;
    char infoLog[1024];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "[PROGRAM LINK ERROR]\n"
                  << infoLog << std::endl;
    }
}

int main() {

    // GLFW Initlization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // GLAD Initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // TRIANGLE VERTICES(HARDCODED) 

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // VBO AND VAO Initlizaiton

    // Creates VAO and VBO variables
    unsigned int VAO, VBO;
    // Assigns VAO Vertex Arrays
    glGenVertexArrays(1, &VAO);
    // Assigns VBO Buffers
    glGenBuffers(1, &VBO);

    // Activate VAO
    glBindVertexArray(VAO);

    // Active VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Upload vertex data to GPU memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // How opengl interperts VAO numbers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Turn on vertex attribute
    glEnableVertexAttribArray(0);

    // ---------- SHADERS ------------

    // Creates the vertex shader (esentially the position of the vertices)
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompile(vertexShader, "VERTEX");

    // Creates the color of each pixel
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompile(fragmentShader, "FRAGMENT");

    // Linker of vertex and fragment shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLink(shaderProgram);
    int offsetLocation = glGetUniformLocation(shaderProgram, "uOffset");

    // Removes shaders after because they have already been loaded
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float speed = 0.02f;

    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {
        // INPUT (continuous)
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            offsetX += speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            offsetX -= speed;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            offsetY += speed;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            offsetY -= speed;

        // clamp-ish feel (optional)
        if (offsetX > 1.0f) offsetX = 1.0f;
        if (offsetX < -1.0f) offsetX = -1.0f;
        if (offsetY > 1.0f) offsetY = 1.0f;
        if (offsetY < -1.0f) offsetY = -1.0f;

        glClearColor(0.2f, 0.5f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // USE SHADER
        glUseProgram(shaderProgram);

        // SEND MOVEMENT TO GPU
        glUniform2f(offsetLocation, offsetX, offsetY);

        // DRAW
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}