#include <engines/physics/body/worldPhysics/physicsRules.hpp>
// cmp
#include <game/cmp/physicsComponent.hpp>
#include <engines/physics/body/bodyComponent.hpp>
// lib
#include <iostream>
#include <algorithm>

void PhysicRules::applyGravity(PhysicsComponent &phy, [[maybe_unused]]bodyComponent &bodyC, [[maybe_unused]]float dt)
{
    if (phy.dynamic_ && phy.use_gravity)
    {
        phy.isInGround = false;
        phy.externForces.y += phy.gravityForce.y * phy.mass;

        if (phy.gravityForce.y == 0)
        {
            phy.isInGround = true;
            phy.gravityForce.y = -9.8f;
        }
    }
}

void PhysicRules::applyMovement(PhysicsComponent &phy, float dt)
{
    if (phy.dynamic_ || phy.kinematic_)
    {
        // limite de fuerza aplicada
        phy.ownForces.x = std::clamp(phy.ownForces.x, -phy.maxForceSprint, phy.maxForceSprint);
        phy.ownForces.z = std::clamp(phy.ownForces.z, -phy.maxForceSprint, phy.maxForceSprint);

        phy.force = phy.ownForces + phy.externForces;
        phy.aceleration = (phy.force / phy.mass);
        phy.velocity = phy.aceleration * dt;
        phy.position += phy.velocity * dt;

        if (phy.isInGround)
        {
            phy.externForces *=0;
        }
    }
}

void PhysicRules::applyAirFriction(PhysicsComponent &phy, [[maybe_unused]]float dt)
{
    if ((!phy.isInGround) && phy.dynamic_)
    {
        float forceVector = glm::sqrt((phy.ownForces.x * phy.ownForces.x) + (phy.ownForces.z * phy.ownForces.z));
        if (forceVector <= 250.f)
        {
            phy.ownForces.x = 0;
            phy.ownForces.z = 0;
        }
        else if (forceVector > 250.f)
        {
            phy.ownForces.x *= phy.air_drag;
            phy.ownForces.z *= phy.air_drag;
        }
    }
}