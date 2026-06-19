#pragma once
#include <string>

class Texture
{
public:
    Texture(const std::string& path);

    ~Texture();
    
    void bind();

private:
    unsigned int ID;
};   