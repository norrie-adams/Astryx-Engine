#pragma once
#include <string>

class Texture
{
public:
    Texture(const std::string &path);

    ~Texture();

    void bind();

    int width = 0;
    int height = 0;
    int nrChannels = 0;

private:
    unsigned int ID;
};