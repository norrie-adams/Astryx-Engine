#pragma once
#include <glad/glad.h>

class Shader {
    public: 
        unsigned int ID;

        Shader(const char* vertexSrc, const char* fragmentSrc);
        void use();

        int getUniform(const std::string& name)
        {
            return glGetUniformLocation(ID, name.c_str());
        }
};