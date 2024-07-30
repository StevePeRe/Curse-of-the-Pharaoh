#include <game/sys/physics.hpp>
// manager
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/physicsComponent.hpp>
// physics
#include <engines/physics/body/worldPhysics/physicsRules.hpp>
#include <engines/physics/body/bodyComponent.hpp>
// util
#include <ecs/util/globals.hpp>
#include <cstdlib>
#include <iostream>

void PhysicsSystem::update(ECS::EntityManager &em, float deltaTime)
{
    for (auto &physics : em.getComponents<PhysicsComponent>())
    {
        auto *e = em.getEntityByID(physics.getEntityID());
        if (e)
        {
            auto *body = e->getComponent<bodyComponent>();
            if (body)
            {
                physics.rules.applyGravity(physics, *body, deltaTime);
                physics.rules.applyAirFriction(physics, deltaTime);
                physics.rules.applyMovement(physics, deltaTime);
            }
        }
    }
}