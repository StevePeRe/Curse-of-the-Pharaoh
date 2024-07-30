#include <game/sys/sensory.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/audioComponent.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <cstdint>
#include <iostream>

void SensorySystem::update(ECS::EntityManager &em)
{
    for (auto &percps : em.getComponents<PerceptionComponent>())
    {
        percps.heard = false;
        auto *e1 = em.getEntityByID(percps.getEntityID());
        if (e1)
        {
            auto *phy1 = e1->getComponent<PhysicsComponent>();
            for (auto &physicsB : em.getComponents<PhysicsComponent>()) // de la entidad a la que dirijo el raycast
            {
                auto *e2 = em.getEntityByID(physicsB.getEntityID());
                if (e2 && e1 != e2)
                {
                    auto *aud2 = e2->getComponent<AudioComponent>();
                    auto *per2 = e2->getComponent<PerceptionComponent>();
                    if (phy1)
                    {
                        // Para la vista
                        if (percps.hasSigth)
                        {
                            if (percps.layersToDetect.Intersects(percps.raycast.closestObject))
                            {
                                percps.seen = true;
                            }
                            else
                            {
                                percps.seen = false;
                            }
                        }

                        // Para el oido
                        if (percps.hasHearing)
                        {
                            if (aud2 && per2)
                            {
                                for (auto &par : aud2->getSoundMap())
                                { 
                                    auto itr = per2->radioSound.find(par.first);
                                    if (itr == per2->radioSound.end())
                                    { 
                                        continue;
                                    }
                                    if (par.second && par.second->GetState() == AudioInstance::AudioState::PLAYING)
                                    {
                                        if (itr->second != 0 && std::abs((physicsB.position.x + itr->second) - phy1->position.x) <= 11.5f && std::abs((physicsB.position.z + itr->second) - phy1->position.z) <= 11.5f && std::abs(physicsB.position.y - phy1->position.y) <= 3.f)
                                        {
                                            percps.heard = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}