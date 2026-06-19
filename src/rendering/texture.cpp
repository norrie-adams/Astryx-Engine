#include "Texture.h"
#include "../../external/glad/include/glad/glad.h"
#include "core/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"

Texture::Texture(const char* path)
{
    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;

    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format = GL_RGB;
        if (nrChannels == 4) {
            format = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        Log::error("Failed to load texture at path: " + *path);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}
