#pragma once

#include "../rendering/Mesh.hpp"
#include "../rendering/Shader.hpp"
#include "ecs/components/Transform.hpp"

class GameObject {
public:
    Mesh mesh;
    Transform transform;

    GameObject(float *vertices, unsigned int size) : mesh(vertices, size) {}

    void draw(Shader &shader);
};
