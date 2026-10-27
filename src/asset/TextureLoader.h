#pragma once
#include <string>

namespace AssetLoader {
    unsigned char* loadTexture(const std::string& filePath, int& width, int& height, int& nrChannels);
}