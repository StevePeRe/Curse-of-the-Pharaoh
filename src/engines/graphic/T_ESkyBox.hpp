#pragma once

#include <engines/graphic/TEntity.hpp>
#include <engines/graphic/TNode.hpp>

struct GraphicEngine;

// La camara hereda de Entity
struct T_ESkyBox : public TEntity
{
    T_ESkyBox(std::array<std::string, 6> faces);
    void draw(GraphicEngine *ge, TNode *node);

    
    private:
        unsigned int VBO, VAO, EBO;
        unsigned int textureId{0};        
        
};