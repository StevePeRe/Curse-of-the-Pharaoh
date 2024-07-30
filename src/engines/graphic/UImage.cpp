#include <engines/graphic/UImage.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <iostream>

#pragma GCC diagnostic ignored "-Wconversion"

UImage::UImage(RTexture *textura, glm::vec2 imagePos, int scrWidth, int scrHeigth)
{
    // Proporcion de la imagen segun la pantalla
    float auxW = textura->width * (scrWidth / 1920.0f);
    float auxH = textura->heigth * (scrHeigth / 1080.0f);
    float realWidth = (auxW - scrWidth / 2) / (scrWidth / 2);
    float realHeigth = (scrHeigth - auxH - (scrHeigth / 2)) / (scrHeigth / 2);

    width = auxW;
    heigth = auxH;

    float vertices[] = {
        // positions          // colors           // texture coords
        -1.0f, realHeigth, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,    // bottom left
        -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,          // top left
        realWidth, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,      // top right
        realWidth, realHeigth, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f // bottom right
    };

    unsigned int indices[] = {
        0, 1, 2, 0, 3, 2};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    id = textura->id;
    glBindVertexArray(0);

    this->imagePos = imagePos;
}

UImage::~UImage()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void UImage::draw(RShader *shader)
{
    if (isVisible)
    {
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, id);

        float x = (imagePos.x - (1920.0f / 2.0f)) / (1920.0f / 2.0f) + 1;
        float y = ((1080.0f / 2.0f) - imagePos.y) / (1080.0f / 2.0f) - 1;

        auto pos = glm::translate(glm::mat4(1.0f), {x, y, 0});

        shader->setMat4("position", pos);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}