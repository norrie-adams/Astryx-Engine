#include "GameObject.h"

void GameObject::draw(Shader& shader)
{
    shader.use();

    glm::mat4 model = transform.getModelMatrix();

    glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &model[0][0]);

    mesh.draw();
}