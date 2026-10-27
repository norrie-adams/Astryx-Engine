#include "AssetManager.h"
#include "ModelLoader.h"
#include "ecs/Registry.h"
#include "core/Log.h"
#include "rendering/Mesh.h"
#include "ecs/components/MeshRenderer.h"
#include "ecs/components/Texture.h"
#include "TextureLoader.h"
#include "rendering/Texture.h"
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

    m_modelFilePaths[assetHash] = filePath;

    AssetLoader::ModelData model = AssetLoader::loadModel(filePath);
    std::vector<float> modelData = AssetLoader::buildMeshData(model);
    m_Models[assetHash] = std::make_unique<Mesh>(modelData.data(), modelData.size());

    return assetHash;
};

assetHash AssetManager::registerTexture(std::string filePath) {
    assetHash textureHash = hashAsset(filePath.c_str());
    
    auto it = m_Textures.find(textureHash);
    if (it != m_Textures.end()) {
        return textureHash;
    }

    m_textureFilePaths[textureHash] = filePath;
    m_Textures[textureHash] = std::make_unique<Texture>(filePath);

    return textureHash;
}


Mesh* AssetManager::getMesh(assetHash hash) {
    auto it = m_Models.find(hash);
    if (it != m_Models.end()) {
        return it->second.get();
    }
    return nullptr;
};

Texture* AssetManager::getTexture(assetHash hash) {
    auto it = m_Textures.find(hash);
    if (it != m_Textures.end()) {
        return it->second.get();
    }
    return nullptr;
}

bool AssetManager::init() {
    auto& meshRendererPool = m_Registry->getPool<MeshRenderer>();
    auto& texturePool = m_Registry->getPool<TextureComponent>();

    // Meshes
    if (meshRendererPool.m_componentData.empty()) {
        Log::error("No entites have a MeshRenderer component. Will not render anything");
        // Will eventually set to default scene
        return false;
    }
    for (auto& component : meshRendererPool.m_componentData) {
        assetHash modelHash = registerModel(component.modelFilePath);
    };

    // Textures
    if (texturePool.m_componentData.empty()) {
        Log::error("No entites have a texture compoent. No texture will be drawn");
        return false;
    }
    for (auto& component : texturePool.m_componentData) {
        assetHash textureHash = registerTexture(component.textureFilePath);
    }
    return true;
}