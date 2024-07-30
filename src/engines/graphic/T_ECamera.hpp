#pragma once

#include <engines/graphic/TEntity.hpp>
#include <engines/graphic/TNode.hpp>

struct GraphicEngine;

// La camara hereda de Entity
struct T_ECamera : public TEntity
{
    void draw(GraphicEngine *ge, TNode *node);

    glm::mat4 GetViewMatrix();
    glm::mat4 getCameraMatrix();
    glm::vec3 getTarget();
    glm::vec3 getPosition();
    glm::vec3 getUp();
    float getFovy();

    void setTarget(glm::vec3 front);
    void setFovy(float fovyAux);
    void setUp(glm::vec3 up);
    void setPosition(glm::vec3 position);

    private:
        // Parametros de la camara_
        glm::vec3 target_{0,0,0};
        glm::vec3 position_{0,0,0};
        glm::vec3 up_{0,1,0};
        float near {0.1f};
        float far {3000};
        float fovy {65.0f};
        
};