#pragma once

#include <glm/glm.hpp>
#include <engines/graphic/Affector.hpp>
#include <engines/graphic/TNode.hpp>


struct AffectorDirection : Affector
{
    AffectorDirection(glm::vec3 dr, float sp) : direction{dr}, speed{sp} {}

    ~AffectorDirection() {};
    
    void affect(TNode *node, double dt) {
        glm::vec3 n = glm::normalize(direction);
        n *= speed;
        node->translate(n);
    }

    AFFECTOR_TYPE getType() { return AFFECTOR_TYPE::DIRECTION; }

    private:
        glm::vec3 direction;
        float speed;
};