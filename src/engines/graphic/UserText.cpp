#include <engines/graphic/UserText.hpp>
#include <engines/graphic/TextData.hpp>
#include <iostream>

void UserText::addText(std::unique_ptr<TextData> text)
{
    std::vector<std::unique_ptr<TextData>>::iterator text_ptr;
    for (text_ptr = textList.begin(); text_ptr != textList.end(); text_ptr++)
    {
        if (text->getText() == (*text_ptr).get()->getText())
        {
            return;
        }
    }
    textList.emplace_back(std::move(text)).get();
}
void UserText::eraseText(std::string text)
{
    std::vector<std::unique_ptr<TextData>>::iterator text_ptr;
    for (text_ptr = textList.begin(); text_ptr != textList.end(); text_ptr++)
    {
        if (text == (*text_ptr).get()->getText())
        {
            textList.erase(text_ptr);
            return;
        }
    }
}
bool UserText::getText(std::string text)
{
    std::vector<std::unique_ptr<TextData>>::iterator text_ptr;
    for (text_ptr = textList.begin(); text_ptr != textList.end(); text_ptr++)
    {
        if (text == (*text_ptr).get()->getText())
        {
            return true;
        }
    }
    return false;
}
void UserText::setText(const char* text)
{
    std::vector<std::unique_ptr<TextData>>::iterator text_ptr;
    for (text_ptr = textList.begin(); text_ptr != textList.end(); text_ptr++)
    {
        if (text == (*text_ptr).get()->getText())
        {
            (*text_ptr).get()->setText(text);
        }
    }
}
void UserText::clear()
{
    textList.clear();
}