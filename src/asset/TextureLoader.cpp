#include "TextureLoader.h"
#include <string>
#include "stb/stb_image.h"
#include "core/Log.h"

namespace AssetLoader {

    unsigned char* loadTexture(const std::string& filePath, int& width, int& height, int& nrChannels) {
        
        stbi_set_flip_vertically_on_load(true);
        unsigned char* pixelData = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

        Log::info("Loaded texture at path: " + filePath);
        return pixelData;
    }

}
