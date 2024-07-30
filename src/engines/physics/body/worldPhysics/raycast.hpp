#pragma once
// PE
#include <engines/physics/body/worldPhysics/raycastResult.hpp>
// utils
#include <game/util/LayerMask.hpp>
// libs
#include <glm/glm.hpp>
#include <cstdint>
#include <iostream>

struct bodyComponent;
struct PhysicsComponent;
struct BoundingBox_PE;

struct Raycast
{
    explicit Raycast() = default;

    bool checkObjectCollision(bodyComponent& body, PhysicsComponent& phy, bool useLayer = false);
    bool checkObjectCollisionCone(bodyComponent &body, PhysicsComponent& phy, uint32_t steps);
    bool checkDetectionCone(PhysicsComponent &phyOrigin, PhysicsComponent &phyToDetect);
    void resetClosestPosition();

    glm::vec3 origin{0.f}; // punto de origen del raycast
    glm::vec3 direction{0.f}; // direccion
    float range{14.5f}; // rango del raycast
    float rangeVisionCone{11.5f}; // rango de vision en Cono

    LayerMask closestObject{};
    float closestPos{FLT_MAX}; // voy iterando por cada objeto para ver si existe alguno mas cercano

    RaycastResult result{}; // para saber los datos de la colision
    LayerMask layer{}; // layer que puede ver el raycast
};