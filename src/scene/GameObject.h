#pragma once

#include "../rendering/Mesh.h"
#include "../rendering/Shader.h"
#include "Transform.h"

class GameObject
{
public:
    Mesh mesh;
    Transform transform;

    GameObject(float* vertices, unsigned int size)
        : mesh (vertices, size) {}

    void draw(Shader& shader);
};