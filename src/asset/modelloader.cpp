// ModelLoader (v0.1)
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
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include "core/Log.h"

namespace Loader {

    // Loads and parses OBJ file into ModelData structure
    ModelData loadModel(const std::string& filename) {
        std::ifstream file(filename);
        ModelData data;

        if (!file.is_open()) {
            Log::error("Failed to load model: " + filename);
            Log::error("Current working directory: " + std::filesystem::current_path().string());
            return data;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            
            if (!(iss >> prefix)) continue;

            // Parse Vertices
            if (prefix == "v") {
                double tempX, tempY, tempZ;
                if (iss >> tempX >> tempY >> tempZ) {
                    data.vertices.push_back(Vertex{tempX, tempY, tempZ});
                }
            }

            // Parse Texture UV Coordinates
            else if (prefix == "vt") {
                float tempU, tempV;
                if (iss >> tempU >> tempV) {
                    data.texCoords.push_back(TexCoord{tempU, tempV});
                } 
            }

            // Parse Faces
            else if (prefix == "f") {
                std::string b1, b2, b3;
                if (iss >> b1 >> b2 >> b3) {
                    // Converts slashes to spaces
                    for (char& c : b1) if (c == '/') c = ' ';
                    for (char& c : b2) if (c == '/') c = ' ';
                    for (char& c : b3) if (c == '/') c = ' ';

                    std::istringstream ss1(b1), ss2(b2), ss3(b3);
                    int vIdx1 = 0, vtIdx1 = 0, vnIdx1 = 0;
                    int vIdx2 = 0, vtIdx2 = 0, vnIdx2 = 0;
                    int vIdx3 = 0, vtIdx3 = 0, vnIdx3 = 0;

                    ss1 >> vIdx1 >> vtIdx1 >> vnIdx1;
                    ss2 >> vIdx2 >> vtIdx2 >> vnIdx2;
                    ss3 >> vIdx3 >> vtIdx3 >> vnIdx3;

                    // Ensures UV index is valid (fallback to first UV if missing)
                    if (vtIdx1 < 1) vtIdx1 = 1;
                    if (vtIdx2 < 1) vtIdx2 = 1;
                    if (vtIdx3 < 1) vtIdx3 = 1;

                    data.faces.push_back(Face{
                    IndexGroup{vIdx1 - 1, vtIdx1 - 1},
                    IndexGroup{vIdx2 - 1, vtIdx2 - 1},
                    IndexGroup{vIdx3 - 1, vtIdx3 - 1}
                });
                }
            }
        }
        
        file.close();
        return data; 
    }

    // Expands indexed face data into a flat float array for OpenGL rendering
    // Output format per vertex: [x, y, z, u, v]
    std::vector<float> buildMeshData(const ModelData& data) {
        std::vector<float> meshData;

        TexCoord fallbackUV{0.0f, 0.0f};

        for (const auto& face : data.faces) {

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