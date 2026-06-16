#pragma once

#include <glad/glad.h>
#include <string>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    int getUniform(const std::string& name) 
    {
        return glGetUniformLocation(ID, name.c_str());
    }
};