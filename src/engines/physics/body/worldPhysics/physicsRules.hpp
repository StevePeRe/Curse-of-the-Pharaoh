#pragma once
#include <glm/glm.hpp>

struct bodyComponent;
struct PhysicsComponent;
struct BoundingBox_PE;

struct PhysicRules
{
    explicit PhysicRules() = default;

    void applyGravity(PhysicsComponent& phy, bodyComponent& body, float dt);    
    void applyAirFriction(PhysicsComponent& phy, float dt);
    void applyMovement(PhysicsComponent& phy, float dt);

private:
};