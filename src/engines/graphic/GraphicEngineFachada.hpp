#pragma once

#include <glm/glm.hpp>
#include <engines/graphic/TNode.hpp>

struct GraphicEngineFachada
{
    virtual ~GraphicEngineFachada() = default;

    virtual bool isRunning() = 0;
    virtual void drawAll() = 0;
    virtual void endScene() = 0;
    // Get Node

    virtual void clearUserInterface() = 0;
    virtual void clearModels() = 0;

protected:
};
