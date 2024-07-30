#pragma once

#include <engines/graphic/RTexture.hpp>
#include <engines/graphic/RShader.hpp>
#include <glm/glm.hpp>

struct UImage
{
    explicit UImage(RTexture* textura, glm::vec2 imagePos, int scrWidth, int scrHeigth);
    ~UImage();
    void draw(RShader *shader);
    // Set position
    void setPosition(glm::vec2 imagePos) { this->imagePos = imagePos; }
    glm::vec2 getPosition() { return imagePos; }
    void setVisible(bool isVisibleImg) { isVisible = isVisibleImg;}
    bool getIsVisible() { return isVisible; }

    int getWidth() { return width; }
    int getHeigth() { return heigth; }
    void setWidth(int w) { width = w; }
    void setHeigth(int h) { heigth = h; }

    private:
        unsigned int id, VAO, VBO, EBO;
        glm::vec2 imagePos{0,0};
        int width{0};
        int heigth{0};
        bool isVisible{true};

};