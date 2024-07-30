#include <engines/graphic/UserInterface.hpp>
#include <iostream>

UserInterface::UserInterface(RShader *shader) : shader{shader} {}


UImage *UserInterface::addImage(std::unique_ptr<UImage> image)
{
    // std::unique_ptr<UImage> &&temp = std::move(image);
    return imageList.emplace_back(std::move(image)).get();
}

void UserInterface::draw()
{
    glDepthFunc(GL_ALWAYS);
    for (auto image = imageList.begin(); image < imageList.end(); image++)
    {
        if ((*image)->getIsVisible())
        {
            shader->use();
            (*image)->draw(shader);
        }
    }
}
void UserInterface::eraseImage(UImage *image)
{
    std::vector<std::unique_ptr<UImage>>::iterator img_ptr;
    for (img_ptr = imageList.begin(); img_ptr != imageList.end(); img_ptr++)
    {
        if (image == (*img_ptr).get())
        {
            imageList.erase(img_ptr);
            return;
        }
    }
}
bool UserInterface::setImageVisibility(UImage *image, bool visible)
{
    std::vector<std::unique_ptr<UImage>>::iterator img_ptr;
    for (img_ptr = imageList.begin(); img_ptr != imageList.end(); img_ptr++)
    {
        if (image == (*img_ptr).get())
        {
            (*img_ptr).get()->setVisible(visible);
            return (*img_ptr).get()->getIsVisible();
        }
    }
}
void UserInterface::setImagePosition(UImage *image, float posX, float posY)
{
    std::vector<std::unique_ptr<UImage>>::iterator img_ptr;
    for (img_ptr = imageList.begin(); img_ptr != imageList.end(); img_ptr++)
    {
        if (image == (*img_ptr).get())
        {
            (*img_ptr).get()->setPosition({posX, posY});
        }
    }
}
void UserInterface::clear()
{
    imageList.clear();
}