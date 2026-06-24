// Mesh 
//
// Responsible for storing vertex data on the GPU
//
// Uses:
// VBO - Stores Vertex Data
// VAO - Describe vertex layout
//
// Vertex Format:
// [x, y, z, u, v]
//
// Attribute 0 -> Position Coordinates
// Attribute 1 -> Texture Coordinates
//
// draw() renders the mesh using GL_TRIANGLES

#include "Mesh.h"

Mesh::Mesh(float* vertices, unsigned int vertexCount)
{
    // 3 Position (X, Y, Z) 2 Texture (U, V)
    count = vertexCount / 5;

    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // Upload Vertex Data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

    GLsizei stride = 5 * sizeof(float);

    // Position Pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // Texture Pointer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Mesh::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, count); 
}