#pragma once

#include <engines/graphic/TEntity.hpp>
#include <engines/graphic/TNode.hpp>

struct GraphicEngine;

// La billboard hereda de Entity
struct T_EBillboard : public TEntity
{
    T_EBillboard() = default;
    T_EBillboard(unsigned int id);
    void draw(GraphicEngine *ge, TNode *node);  
    void setVertex(); 

    private:
        unsigned int VBO, VAO, EBO;
        unsigned int textureId{0};  
        
};