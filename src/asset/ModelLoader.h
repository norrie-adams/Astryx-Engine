#pragma once
#include <vector>
#include <string>

namespace Loader {
    struct Vertex { double x; double y; double z; };
    struct Face { int v1, v2, v3; };

    struct ModelData {
        std::vector<Vertex> vertices;
        std::vector<Face> faces;
    };

    ModelData loadModel(const std::string& filename);

    std::vector<float> buildMeshData(const ModelData& data);
}