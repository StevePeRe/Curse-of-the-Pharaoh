#pragma once

#include <memory>
#include <vector>

struct RShader;
struct TextData;

struct UserText
{

public:
    void addText(std::unique_ptr<TextData> text);
    void eraseText(std::string text);
    bool getText(std::string text);
    void setText(const char* text);

    void clear();

    std::vector<std::unique_ptr<TextData>> textList{};

private:
};
