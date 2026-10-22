#include "AssetManager.h"
#include "ModelLoader.h"
#include "ecs/Registry.h"
#include "core/Log.h"
#include "rendering/Mesh.h"
#include <functional>
#include <cstdint>
#include <memory>

// 64-bit FNV-1a constants
constexpr uint64_t FNV_OFFSET_BASIS = 14695981039346656037ULL;
constexpr uint64_t FNV_PRIME = 1099511628211ULL;

constexpr uint64_t AssetManager::hashAsset(const char* str) {
    if (!str) return 0; 

    uint64_t hash = FNV_OFFSET_BASIS;

    while (*str) {
        hash ^= static_cast<uint8_t>(*str);
        hash *= FNV_PRIME;
        str++;
    }

    return hash;
}

assetHash AssetManager::registerModel(std::string &filePath) {
    assetHash assetHash = hashAsset(filePath.c_str());

    auto it = m_Models.find(assetHash);
    if (it != m_Models.end()) {
        return assetHash;
    };

    m_filePaths[assetHash] = filePath;

    Loader::ModelData model = Loader::loadModel(filePath);
    std::vector<float> modelData = Loader::buildMeshData(model);
    m_Models[assetHash] = std::make_unique<Mesh>(modelData.data(), modelData.size());

    return assetHash;
};

Mesh* AssetManager::getMesh(assetHash hash) {
    auto it = m_Models.find(hash);
    if (it != m_Models.end()) {
        return it->second.get();
    }
    return nullptr;
};

bool AssetManager::init() {
    auto& meshRendererPool = g_Registry.getPool<MeshRenderer>();

    if (meshRendererPool.m_componentData.empty()) {
        Log::error("No entites have a MeshRenderer component. Will not render anything");
        // Will eventually set to default scene
        return false;
    }

    for (auto& component : meshRendererPool.m_componentData) {
        assetHash modelHash = registerModel(component.modelFilePath);
    };

    return true;
}