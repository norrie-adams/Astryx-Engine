#include "ModelLoader.h"
#include "core/Log.h"
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include <iostream>

namespace Loader {

// Fixed forward declarations to use exact types matching ModelLoader.h
void processNode(aiNode* node, const aiScene* scene, ModelData& data, unsigned int& vertexOffset);
void processMesh(aiMesh* mesh, const aiScene* scene, ModelData& data, unsigned int& vertexOffset);

ModelData loadModel(const std::string &filename) {
    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;

    ModelData data;
    Assimp::Importer importer;
    
    // ASSIMP_FLAGS is visible here from ModelLoader.h
    const aiScene* scene = importer.ReadFile(filename, ASSIMP_FLAGS);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        Log::error(importer.GetErrorString());
        return data;
    }
    
    unsigned int vertexOffset = 0;
    processNode(scene->mRootNode, scene, data, vertexOffset);
    
    return data;
}

void processNode(aiNode* node, const aiScene* scene, ModelData& data, unsigned int& vertexOffset) {
    // Process meshes attached to this node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene, data, vertexOffset);
    }
    
    // Recursively process children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, data, vertexOffset);
    }
}

void processMesh(aiMesh* mesh, const aiScene* scene, ModelData& data, unsigned int& vertexOffset) {
    // Single loop optimization for data cache locality
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Positions
        data.vertices.push_back(Vertex{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
        
        // Normals
        if (mesh->HasNormals()) {
            data.normals.push_back(Normal{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z});
        } else {
            data.normals.push_back(Normal{0.0f, 1.0f, 0.0f});
        }
        
        // UV Texture Coordinates (Channel 0)
        if (mesh->mTextureCoords[0]) {
            data.texCoords.push_back(TexCoord{mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
        } else {
            data.texCoords.push_back(TexCoord{0.0f, 0.0f});
        }
    }
    
    // Process faces with the absolute global index offset offset applied
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        
        if (face.mNumIndices == 3) {
            unsigned int idx0 = face.mIndices[0] + vertexOffset;
            unsigned int idx1 = face.mIndices[1] + vertexOffset;
            unsigned int idx2 = face.mIndices[2] + vertexOffset;
            
            data.faces.push_back(Face{
                {idx0, idx0},
                {idx1, idx1},
                {idx2, idx2}
            });
        }
    }
    
    // Cascade vertex offset forward for multi-mesh objects
    vertexOffset += mesh->mNumVertices;
}

std::vector<float> buildMeshData(const ModelData &data) {

    std::vector<float> meshData;
    
    for (const auto &face : data.faces) {
        // Vertex 1
        Vertex v1 = data.vertices[face.c1.vIdx];
        meshData.push_back(static_cast<float>(v1.x));
        meshData.push_back(static_cast<float>(v1.y));
        meshData.push_back(static_cast<float>(v1.z));
        TexCoord uv1 = data.texCoords[face.c1.vtIdx];
        meshData.push_back(uv1.u);
        meshData.push_back(uv1.v);
        Normal n1 = data.normals[face.c1.vIdx];
        meshData.push_back(n1.nx); meshData.push_back(n1.ny); meshData.push_back(n1.nz);

        // Vertex 2
        Vertex v2 = data.vertices[face.c2.vIdx];
        meshData.push_back(static_cast<float>(v2.x));
        meshData.push_back(static_cast<float>(v2.y));
        meshData.push_back(static_cast<float>(v2.z));
        TexCoord uv2 = data.texCoords[face.c2.vtIdx];
        meshData.push_back(uv2.u);
        meshData.push_back(uv2.v);
        Normal n2 = data.normals[face.c2.vIdx];
        meshData.push_back(n2.nx); meshData.push_back(n2.ny); meshData.push_back(n2.nz);

        // Vertex 3
        Vertex v3 = data.vertices[face.c3.vIdx];
        meshData.push_back(static_cast<float>(v3.x));
        meshData.push_back(static_cast<float>(v3.y));
        meshData.push_back(static_cast<float>(v3.z));
        TexCoord uv3 = data.texCoords[face.c3.vtIdx];
        meshData.push_back(uv3.u);
        meshData.push_back(uv3.v);
        Normal n3 = data.normals[face.c3.vIdx];
        meshData.push_back(n3.nx); meshData.push_back(n3.ny); meshData.push_back(n3.nz);
    }
    return meshData;
}

} // namespace Loader
