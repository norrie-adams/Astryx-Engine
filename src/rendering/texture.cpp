// Texture
//
// Responsible for loading an image from disk and turns it into a GPU texture that can be used in rendering
//
// Uses stbi_load() to load the texture data to the RAM and then later gives to GPU memory with glTexImage2D()
//
/// Determines texture format (RGB vs RGBA) based on number of channels

#include "Texture.h"
#include "../../external/glad/include/glad/glad.h"
#include "core/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"

Texture::Texture(const std::string& path)
{
    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    
    if (data)
    {
        GLenum internalFormat = GL_RGB;
        GLenum dataFormat = GL_RGB;

        if (nrChannels == 1) {
            internalFormat = GL_RED;
            dataFormat = GL_RED;
        }
        else if (nrChannels == 3) {
            internalFormat = GL_RGB;  // How GPU stores it
            dataFormat = GL_RGB;      // How stbi loaded it
        }
        else if (nrChannels == 4) {
            internalFormat = GL_RGBA;
            dataFormat = GL_RGBA;
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    stbi_image_free(data);
}


Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}
