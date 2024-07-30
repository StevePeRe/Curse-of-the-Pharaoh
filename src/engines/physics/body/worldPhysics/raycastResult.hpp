#pragma once
// utils
#include <ecs/util/globals.hpp>
// libs
#include <glm/glm.hpp>

struct RaycastResult
{
    explicit RaycastResult() = default;

    float distance{0.f}; // distancia de interseccion
    glm::vec3 intersection{0.f}; // punto de interseccion

    bool has_intersection{false}; // colision

};
