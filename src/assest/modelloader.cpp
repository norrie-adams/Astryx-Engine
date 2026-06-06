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
            
            if (std::filesystem::exists("assets")) {
                Log::info("Contents of the 'assets' directory:");
                for (const auto& entry : std::filesystem::directory_iterator("assets")) {
                    Log::info(" - " + entry.path().filename().string());
                }
            } else {
                Log::error("The 'assets' directory does NOT exist in this working directory!");
            }
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

} 