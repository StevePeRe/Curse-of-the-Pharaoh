#pragma once

#include <glm/glm.hpp>

struct SCharacter
{
    unsigned int textureId;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};