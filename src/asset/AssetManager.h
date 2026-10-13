#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <cstdint>
#include <string>

using assetHash = uint64_t;

class AssetManager {
    // Storage Components
    std::unordered_map<assetHash, std::unique_ptr<std::vector<float>>> m_Models;
    std::unordered_map<assetHash, std::unique_ptr<std::vector<float>>> m_Textures;
    // File Paths
    std::unordered_map<assetHash, std::string> m_filePaths;

    assetHash hashAsset(std::string &filepath);
    assetHash registerModel(std::string &filepath);
};