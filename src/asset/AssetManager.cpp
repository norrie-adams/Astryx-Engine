#include "AssetManager.h"
#include <functional>
#include <cstdint>

assetHash hashAsset() {
    uint64_t key = 123456789012345ULL;

    std::hash<uint64_t> hasher;
    uint64_t hashAsset = hasher(key); 

    return hashAsset; 
};
