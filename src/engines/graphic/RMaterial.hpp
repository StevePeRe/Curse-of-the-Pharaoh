#pragma once

#include <engines/graphic/Resource.hpp>
#include <string>
#include <array>

struct RMaterial : public Resource
{
    void loadResource(std::string resource);

    float diffuse, ambient, specular;
};
