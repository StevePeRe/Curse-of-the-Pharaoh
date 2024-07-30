#pragma once

#include <engines/graphic/Resource.hpp>
#include <engines/graphic/SCharacter.hpp>
#include <string>
#include <map>
#include <GLAD/src/glad.h>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

struct RFont : public Resource
{
    void loadResource(std::string fileName);
    void loadFont(std::string const fileName);

    std::map<GLchar, SCharacter> characters;
    unsigned int VBO, VAO;
};