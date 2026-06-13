#include "ModelLoader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "core/Log.h"
#include <filesystem>

namespace Loader {

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

            // Parse Faces
            else if (prefix == "f") {
                std::string b1, b2, b3;
                if (iss >> b1 >> b2 >> b3) {
                    for (char& c : b1) if (c == '/') c = ' ';
                    for (char& c : b2) if (c == '/') c = ' ';
                    for (char& c : b3) if (c == '/') c = ' ';

                    std::istringstream ss1(b1), ss2(b2), ss3(b3);
                    int vIdx1 = 0, vIdx2 = 0, vIdx3 = 0;

                    ss1 >> vIdx1;
                    ss2 >> vIdx2;
                    ss3 >> vIdx3;

                    data.faces.push_back(Face{vIdx1 - 1, vIdx2 - 1, vIdx3 - 1});
                }
            }
        }

        file.close();
        return data; 
    }

    std::vector<float> buildMeshData(const ModelData& data) {
        std::vector<float> meshData;

        for (const auto& face : data.faces) {
            Vertex v1 = data.vertices[face.v1];
            meshData.push_back(static_cast<float>(v1.x));
            meshData.push_back(static_cast<float>(v1.y));
            meshData.push_back(static_cast<float>(v1.z));

            Vertex v2 = data.vertices[face.v2];
            meshData.push_back(static_cast<float>(v2.x));
            meshData.push_back(static_cast<float>(v2.y));
            meshData.push_back(static_cast<float>(v2.z));

            Vertex v3 = data.vertices[face.v3];
            meshData.push_back(static_cast<float>(v3.x));
            meshData.push_back(static_cast<float>(v3.y));
            meshData.push_back(static_cast<float>(v3.z));
        }
        return meshData;
    }
} 