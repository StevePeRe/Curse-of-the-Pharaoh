#pragma once

#include <engines/graphic/TEntity.hpp>
#include <engines/graphic/TNode.hpp>

struct GraphicEngine;

// La luz hereda de Entity
struct T_ELight : public TEntity
{
    ~T_ELight();
    void draw(GraphicEngine *ge, TNode *node);

    private:
        // Parametros de la luz Max: Blanco(1,1,1) - Min: Negro(0,0,0) esto es para la intensidad 
        // de la luz si por ejemplo necesitamos que la luz sea algo roja ponemos (1,0,0)
        glm::vec3 intensity;
        unsigned int lightCubeVAO, VBO, cubeVAO;
        
};