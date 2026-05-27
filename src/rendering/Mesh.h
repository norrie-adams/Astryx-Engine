#pragma once
#include <glad/glad.h>

class Mesh {
    public: 
        Mesh(float* vertices, unsigned int vertexCount);
        void draw();

    private:
        unsigned int VAO, VBO;
        unsigned int count;
};