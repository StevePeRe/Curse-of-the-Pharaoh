#pragma once

#include <memory>
#include <vector>
#include <engines/graphic/UImage.hpp>

struct RShader;

struct UserInterface
{
    public:

        UserInterface(RShader *shader);

        UImage* addImage(std::unique_ptr<UImage> image);
        void eraseImage(UImage* image);
        bool setImageVisibility(UImage *image, bool visible);
        void setImagePosition(UImage *image, float posX, float posY);

        void draw();
        void clear();

        size_t getImageList() { return imageList.size(); }

    private:
        std::vector<std::unique_ptr<UImage>> imageList{};
        RShader* shader{};
};
