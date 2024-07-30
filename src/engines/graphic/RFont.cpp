#include <engines/graphic/RFont.hpp>
#include <cstdint>

void RFont::loadResource(std::string fileName)
{
    this->setName(fileName);
    loadFont(fileName);
}
void RFont::loadFont(std::string fileName)
{
//     // printf("CARGANDO FUENTE %s\n", filename.c_str());
    
    // Check if FT_Library is actually ready to use
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        return;
    }

    FT_Face face;
    //Filepath name with .ftt at the end, not as bitmap
    fileName = "./media/font/" + fileName;
    if (FT_New_Face(ft, fileName.c_str(), 0, &face)) {
        return;
    }

    // // Select font size, with width = 0 and height = (3ยบ value)
    FT_Set_Pixel_Sizes(face, 0, 48);

    // // Library tries to load a single char, for exemple, 'X'
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        return;
    }

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Loop for every char you want to load at map
    for (unsigned char c = 0; c < 252; c++)
    {
        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            continue;
        }

        // Generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Now store character for later use
        SCharacter character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        // At the end of the loop, insert the character to map
        characters.insert(std::pair<char, SCharacter>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}