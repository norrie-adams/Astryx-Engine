// GameObject
//
// Represents a renderable object in the scene
//
// Responsibilities:
// - Stores transform (position, rotation, scale)
// - Provides model matrix for rendering
// - Delegates actual drawing to its Mesh

#include "GameObject.h"

void GameObject::draw(Shader& shader)
{
    glm::mat4 model = transform.getModelMatrix();

    glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, &model[0][0]);

    mesh.draw();
}