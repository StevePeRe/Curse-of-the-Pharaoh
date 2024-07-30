#pragma once
// openGL
#include <glm/glm.hpp>

struct bodyComponent;
struct PhysicsComponent;
struct PerceptionComponent;
struct BoundingBox_PE;
struct RaycastResult;

struct AABB
{
    explicit AABB() = default;

    bool checkObjectCollision(bodyComponent &bc1, bodyComponent &bc2, PhysicsComponent &p1, PhysicsComponent &p2);
    void resolveCollisionXZ(PhysicsComponent &phyA, PhysicsComponent &phyB);
    void resolveCollisionY(PhysicsComponent &phyA, PhysicsComponent &phyB);
    void resolveCollisionWithFriction(PhysicsComponent &phyA, PhysicsComponent &phyB);
    BoundingBox_PE turnToScreenCoordinates(const BoundingBox_PE &box, float x, float y, float z);

    bool nearlyEqual(glm::vec3 a, glm::vec3 b);
    bool nearlyEqual(float a, float b);

private:
    glm::vec3 normalY{0.f,0.f,0.f};
};
