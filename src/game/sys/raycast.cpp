#include <game/sys/raycast.hpp>
// manager
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <engines/physics/body/bodyComponent.hpp>
/* #include <game/cmp/powerUpComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
#include <game/cmp/healthComponent.hpp> */
/* #include <game/cmp/renderComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/cameraComponent.hpp>
#include <game/cmp/inputComponent.hpp> */
/* #include <game/cmp/perceptionComponent.hpp> */
/* #include <game/cmp/aiComponent.hpp> */
// physics
/* #include <engines/physics/body/worldPhysics/physicsRules.hpp>
#include <engines/physics/body/bodyComponent.hpp> */
// util
#include <ecs/util/globals.hpp>
#include <cstdlib>
#include <iostream>

void RaycastSystem::update(ECS::EntityManager &em)
{
    for (auto &percps : em.getComponents<PerceptionComponent>())
    {
        if (!percps.useRaycast)
            continue;

        auto *e1 = em.getEntityByID(percps.getEntityID());
        if (e1)
        {
            auto *phy1 = e1->getComponent<PhysicsComponent>();
            for (auto &physics : em.getComponents<PhysicsComponent>()) // de la entidad a la que dirijo el raycast
            {
                auto *e2 = em.getEntityByID(physics.getEntityID());
                if (e2 && e1 != e2)
                {
                    auto *body2 = e2->getComponent<bodyComponent>();
                    if (phy1 && body2)
                    {
                        // el raycast se lanza hacia una direccion
                        if(percps.raycast.checkObjectCollision(*body2, physics, true)) {
                            // std::cout << "inter: " << physics.layer.getMask() << "\n";
                            // std::cout << "----------------------------------------\n";
                            /* break; */
                            // continue; // al momento de detectar uno paso al sigueinte
                        }
                    }
                }
            }
            percps.raycast.resetClosestPosition();
        }
    }
}