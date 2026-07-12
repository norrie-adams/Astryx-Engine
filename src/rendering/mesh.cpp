// Mesh
//
// Represents a GPU-uploaded vertex buffer for rendering geometry.
//
// Data Layout:
// - Interleaved vertex format: [x, y, z, u, v]
// - Attribute 0: position (vec3)
// - Attribute 1: texture coordinates (vec2)
//
// Implementation:
// - Uses VBO to store vertex data in GPU memory
// - Uses VAO to define vertex attribute layout
// - No index buffer (non-indexed rendering)
//
// Notes:
// - Mesh is static after creation (no CPU-side updates)
// - Rendered using GL_TRIANGLES
// - Assumes external renderer handles shader binding

#include "Mesh.h"

// Creates GPU buffers and uploads vertex data
Mesh::Mesh(float *vertices, unsigned int vertexCount)
{
    // Each vertex = 8 floats: 3 position + 2 UV + 3 Normal
    count = vertexCount / 8;

    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // Upload Vertex Data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

    GLsizei stride = 8 * sizeof(float);

    // Position attribute (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute (location 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2); 
}

// Renders mesh using triangles
void Mesh::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, count);
}