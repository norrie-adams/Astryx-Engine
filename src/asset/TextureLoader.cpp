#include "TextureLoader.h"
#include <string>
#include "stb/stb_image.h"

namespace AssetLoader {

    unsigned char* loadTexture(const std::string& filePath, int& width, int& height, int& nrChannels) {
        
        stbi_set_flip_vertically_on_load(true);
        unsigned char* pixelData = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

        return pixelData;
    }

}
