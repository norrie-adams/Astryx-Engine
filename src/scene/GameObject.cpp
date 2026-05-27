#include "GameObject.h"

void GameObject::draw(Shader& shader)
{
    shader.use();

    glUniform3f(
        shader.getUniform("uPos"),
        transform.x,
        transform.y,
        transform.z
    );

    mesh.draw();
}