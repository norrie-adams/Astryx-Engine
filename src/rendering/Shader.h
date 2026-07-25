#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
    unsigned int ID;

    Shader(const char *vertexPath, const char *fragmentPath);

    void use();

    int getUniform(const std::string &name) { return glGetUniformLocation(ID, name.c_str()); }

    // Shader Helper Functions
    void setMat4(const std::string& name, const glm::mat4& value) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));}
    void setVec3(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));}
    void setFloat(const std::string& name, float intensity) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), intensity); }
    void setInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
};

