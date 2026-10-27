#pragma once
#include <string>
#include <vector>
#include <assimp/scene.h>      
#include <assimp/mesh.h>       
#include <assimp/Importer.hpp> 

#define ASSIMP_FLAGS (aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs | aiProcess_GenSmoothNormals)

namespace AssetLoader {

struct Vertex {
    float x, y, z;
};

struct Normal {
    float nx, ny, nz; 
};

struct TexCoord {
    float u, v;
};

// Index of the data in the flat array
struct IndexGroup {
    unsigned int vIdx; // Position
    unsigned int vtIdx; // Texture
};

struct Face {
    IndexGroup c1;
    IndexGroup c2;
    IndexGroup c3;
};

// Full Model Data
struct ModelData {
    std::vector<Vertex> vertices;
    std::vector<Normal> normals;    
    std::vector<TexCoord> texCoords;
    std::vector<Face> faces;
};

ModelData loadModel(const std::string &filename);
void processNode(aiNode* node, const aiScene* scene, ModelData& data, unsigned int& vertexOffset);
void processMesh(aiMesh* mesh, const aiScene* scene, ModelData& data, unsigned int& vertexOffset);
std::vector<float> buildMeshData(const ModelData &data);

}