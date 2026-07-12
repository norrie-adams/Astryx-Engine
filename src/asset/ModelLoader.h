#pragma once
#include <string>
#include <vector>

#define ASSIMP_FLAGS (aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs)

namespace Loader
{

// 1. Define the Normal struct (just like your Vertex struct)
struct Vertex {
    double x, y, z;
};

struct Normal {
    float nx, ny, nz; // Holds the x, y, z direction of the normal
};

struct TexCoord {
    float u, v;
};

// (Keep your Face and Component structs exactly how you have them)
struct IndexGroup {
    unsigned int vIdx;
    unsigned int vtIdx;
};

struct Face {
    IndexGroup c1;
    IndexGroup c2;
    IndexGroup c3;
};

// 2. Add the normals vector to ModelData
struct ModelData {
    std::vector<Vertex> vertices;
    std::vector<Normal> normals;    // <-- ADD THIS LINE
    std::vector<TexCoord> texCoords;
    std::vector<Face> faces;
};

// Your function declarations...
ModelData loadModel(const std::string &filename);
std::vector<float> buildMeshData(const ModelData &data);

}