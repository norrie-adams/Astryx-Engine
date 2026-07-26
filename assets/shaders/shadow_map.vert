// Takes in vertex position
// Multiples LightSpaceMatrix * ModelMatrix
// Outputs gl_Position

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}