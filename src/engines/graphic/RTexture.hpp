#pragma once

#include <engines/graphic/Resource.hpp>
#include <string>
#include <array>

struct RTexture : public Resource
{
    void loadResource(std::string resource);
    void loadTexture(std::string resource);
    unsigned int TextureToCubemap(std::array<std::string, 6> faces);

    unsigned int id;
    int width, heigth;
};
