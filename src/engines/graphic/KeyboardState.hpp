#pragma once

#include <engines/graphic/Window.hpp>

struct KeyboardState
{
    bool keys[GLFW_KEY_LAST] = {false};

    bool isKeyDown(int key) const
    {
        return keys[key];
    }

    bool isKeyPressed(int key) const
    {
        return keys[key] && !keysPrev[key];
    }

    bool isKeyReleased(int key) const
    {
        return !keys[key] && keysPrev[key];
    }

    void update()
    {
        std::copy(std::begin(keys), std::end(keys), std::begin(keysPrev));
    }

private:
    bool keysPrev[GLFW_KEY_LAST] = {false};
};