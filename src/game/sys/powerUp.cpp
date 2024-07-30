#include <game/sys/powerUp.hpp>
// manager
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/powerUpComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
#include <game/cmp/healthComponent.hpp>
/* #include <game/cmp/physicsComponent.hpp>
#include <game/cmp/renderComponent.hpp>
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

void PowerUpSystem::update(ECS::EntityManager &em)
{
    for (auto &powers : em.getComponents<PowerUpComponent>())
    {
        auto *e = em.getEntityByID(powers.getEntityID());
        if (e)
        {
            auto *beh = e->getComponent<ShotBehaviourComponent>();
            auto *hea = e->getComponent<HealthComponent>();


            if(beh){
                if(beh->type != ECS::BehaviourType::Pistol && beh->shot_ammo == 0){
                    beh->type = ECS::BehaviourType::Pistol;
                    beh->shot_ammo = 8;
                    beh->shot_maxAmmo = 8;
                }
                if(powers.layer.ContainsLayer(PowerUps::SHOTGUN_MODE)) {
                
                    beh->type = ECS::BehaviourType::ShotGun;
                    beh->shot_ammo = powers.shots;
                    beh->shot_maxAmmo = powers.shots;
                }
                powers.layer.RemoveLayer(PowerUps::SHOTGUN_MODE);
            }

            if(powers.layer.ContainsLayer(PowerUps::INMUNITY_MODE)) {
                if(hea){
                    hea->inminityHits = powers.inminityHits;
                }
                powers.layer.RemoveLayer(PowerUps::INMUNITY_MODE);
            }
        }
    }
}