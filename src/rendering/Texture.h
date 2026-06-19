#pragma once

class Texture
{
public:
    Texture(const char* path);

    ~Texture();
    
    void bind();

private:
    unsigned int ID;
};   