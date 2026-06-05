#include "ModelLoader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "core/Log.h"
#include <filesystem>

namespace Loader {
    std::vector<Vertex> loadVertices(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<Vertex> vertexList;

        if (!file.is_open()) {
            Log::error("Failed to load model: " + filename);
            Log::error("Current working directory: " + std::filesystem::current_path().string());
            return vertexList;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;

            if (iss >> prefix && prefix == "v") {
                double tempX, tempY, tempZ;

                if (iss >> tempX >> tempY >> tempZ) {
                    Vertex v{tempX, tempY, tempZ};
                    vertexList.push_back(v);
                }
            }
        }

        return vertexList;
    }
}