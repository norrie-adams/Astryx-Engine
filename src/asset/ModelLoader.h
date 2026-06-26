#pragma once
#include <string>
#include <vector>

namespace Loader
{

struct Vertex
{
    double x;
    double y;
    double z;
};

struct TexCoord
{
    float u;
    float v;
};

struct IndexGroup
{
    int vIdx;  // Index for data.vertices
    int vtIdx; // Index for data.texCoords
};

struct Face
{
    IndexGroup c1;
    IndexGroup c2;
    IndexGroup c3;
};

struct ModelData
{
    std::vector<Vertex> vertices;
    std::vector<TexCoord> texCoords;
    std::vector<Face> faces;
};

ModelData loadModel(const std::string &filename);
std::vector<float> buildMeshData(const ModelData &data);
} // namespace Loader