#pragma once
#include <string>
#include <vector>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define ASSIMP_FLAGS (aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs)

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
    unsigned int vIdx;  // Index for data.vertices
    unsigned int vtIdx; // Index for data.texCoords
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

void processNode(aiNode* node, const aiScene* scene, ModelData& data);
void processMesh(aiMesh* mesh, const aiScene* scene, ModelData& data);
} // namespace Loader