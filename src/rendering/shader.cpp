// Shader
//
// Loads GLSL vertex and fragment shader files,
// compiles them, links them into a shader program,
// and provides a way to activate the program for rendering

#include "Shader.h"
#include "core/Log.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Reads a text file into a string
static std::string readFile(const char* filePath)
{
    std::ifstream file(filePath);
    if(!file.is_open())
    {
        Log::error("Failed to open shader file: " + std::string(filePath));
        return "";
    }

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();

    return stream.str();

}

// Compiles a single GLSL shader (vertex/fragment)
static unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        Log::error("Shader compiler error");
    }

    return shader;

}

// Links compiled shaders into a program
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

    std::string vertexStr = readFile(vertexPath);
    std::string fragmentStr = readFile(fragmentPath);

    if (vertexStr.empty() || fragmentStr.empty()) {
        Log::error("Shader source empty");
        return;
    }

    const char* vsSource = vertexStr.c_str();
    const char* fsSource = fragmentStr.c_str();

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vsSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fsSource);

    ID = glCreateProgram();
    glAttachShader(ID, vs);
    glAttachShader(ID, fs);
    glLinkProgram(ID);

    int success;
    char log[1024];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(ID, 1024, nullptr, log);
        Log::error("Shader link error");
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

// Activates the shader program for rendering
void Shader::use() 
{
    glUseProgram(ID);
}