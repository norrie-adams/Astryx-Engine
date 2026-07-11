// ModelLoader
//
// Minimal OBJ file loader that converts model data into a GPU-ready vertex buffer
//
// Pipeline:
// 1. Reads OBJ file from disk
// 2. Parses vertex positions (v)
// 3. Parses texture coordinates (vt)
// 4. Parses triangular faces (f)
// 5. Expands indexed face data into a flat vertex buffer
//
// Limitations:
// - Only supports triangle faces (no quads or polygons)
// - No vertex deduplication (fully expanded vertex buffer)
// - Normals are parsed but not used in final mesh output
// - Assumes valid and well-formed OBJ files

#include "ModelLoader.h"
#include "core/Log.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Loader
{

// Loads and parses OBJ file into ModelData structure
ModelData loadModel(const std::string &filename)
{
    ModelData data;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filename, ASSIMP_FLAGS);

    if (!scene) {
        Log::error(importer.GetErrorString());
        return data;
    }

    processNode(scene->mRootNode, scene, data);

    return data;
}

void processNode(aiNode* node, const aiScene* scene, ModelData& data) {

    // Process meshes attached to node
    for (unsigned int i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        processMesh(mesh, scene, data);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, data);
    }
} 

void processMesh(aiMesh* mesh, const aiScene* scene, ModelData& data) {

    // Loop through vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        data.vertices.push_back(Vertex{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
    }
    
    // Loop through UV Coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        if (mesh->mTextureCoords[0])
        {
            data.texCoords.push_back(TexCoord{mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
        }
        else 
        {
            data.texCoords.push_back(TexCoord{0.0f, 0.0f});
        }
    } 

    // Loop through faces
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        data.faces.push_back( Face{ 
            {face.mIndices[0], face.mIndices[0]}, 
            {face.mIndices[1], face.mIndices[1]}, 
            {face.mIndices[2], face.mIndices[2]} 
        } 
    );
    }
}

// Expands indexed face data into a flat float array for OpenGL rendering
// Output format per vertex: [x, y, z, u, v]
std::vector<float> buildMeshData(const ModelData &data)
{
    std::vector<float> meshData;

    for (const auto &face : data.faces)
    {

        // Position Coordinates
        Vertex v1 = data.vertices[face.c1.vIdx];
        meshData.push_back(static_cast<float>(v1.x));
        meshData.push_back(static_cast<float>(v1.y));
        meshData.push_back(static_cast<float>(v1.z));

        // Texture Coordinates
        TexCoord uv1 = data.texCoords[face.c1.vtIdx];
        meshData.push_back(uv1.u);
        meshData.push_back(uv1.v);

        // Position Coordinates
        Vertex v2 = data.vertices[face.c2.vIdx];
        meshData.push_back(static_cast<float>(v2.x));
        meshData.push_back(static_cast<float>(v2.y));
        meshData.push_back(static_cast<float>(v2.z));

        // Texture Coordinates
        TexCoord uv2 = data.texCoords[face.c2.vtIdx];
        meshData.push_back(uv2.u);
        meshData.push_back(uv2.v);

        // Position Coordinates
        Vertex v3 = data.vertices[face.c3.vIdx];
        meshData.push_back(static_cast<float>(v3.x));
        meshData.push_back(static_cast<float>(v3.y));
        meshData.push_back(static_cast<float>(v3.z));

        // Texture Coordinates
        TexCoord uv3 = data.texCoords[face.c3.vtIdx];
        meshData.push_back(uv3.u);
        meshData.push_back(uv3.v);
    }
    return meshData;
}
}