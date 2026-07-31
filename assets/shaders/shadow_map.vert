#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 m_lightSpaceMatrix;
uniform mat4 model;

void main() 
{
    gl_Position = m_lightSpaceMatrix * model * vec4(aPos, 1.0);
}