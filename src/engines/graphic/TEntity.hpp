#pragma once

#include <glm/glm.hpp>

struct GraphicEngine;
struct TNode;

struct TEntity
{
    //virtual ~TEntity() = default;
    virtual void draw(GraphicEngine *ge, TNode *node) = 0;
};
