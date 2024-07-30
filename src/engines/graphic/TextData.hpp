#pragma once

#include <string>
#include <glm/glm.hpp>

struct TextData
{
public:

    explicit TextData(std::string text, std::string font, float posX, float posY, float textSize, glm::vec3 color) : text_{text}, font_{font},
                posX_{posX}, posY_{posY}, fontSize_{textSize}, color_{color} 
    {}

    std::string getText() { return text_; }
    std::string getFont() { return font_; }
    float getPosX() { return posX_; }
    float getPosY() { return posY_; }
    float getFontSize() { return fontSize_; }
    glm::vec3 getColor() { return color_; }

    void setText(const char *text) { text_ = text; };
    
private:
    std::string text_;
    std::string font_;
    float posX_;
    float posY_;
    float fontSize_;
    glm::vec3 color_;
};
