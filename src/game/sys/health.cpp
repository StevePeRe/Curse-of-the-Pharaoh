#include <game/sys/health.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
#include <game/man/event/eventManager.hpp>
// cmp
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/colliderComponent.hpp>
#include <game/cmp/audioComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
/* // Graphic Engine
#include <engines/graphic/GraphicEngine.hpp> */
// triggers
#include <game/events/damageEvent.hpp>
// util
#include <ecs/util/globals.hpp>

void HealthSystem::update(ECS::EntityManager &em)
{
    auto &eventM = em.getSingletonComponentEM<EventManager>();
    for (auto &health : em.getComponents<HealthComponent>())
    {
        auto *e = em.getEntityByID(health.getEntityID());
        
        if (e)
        {
            if (health.health <= 0)
            {
                e->mark4destruction();
                break;
            }

            if(health.damaged) {

                if (health.inminityHits > 0)
                {
                    health.inminityHits--;
                    // sonido de inminidad al pegarte
                    break;
                }

                auto *rend = e->getComponent<RenderComponent>();
                auto *audio = e->getComponent<AudioComponent>();

                if (!health.hasInmunity)
                {
                    health.damaged = false;

                    if (audio)
                    {
                        switch (e->getType())
                        {
                        case ECS::EntityType::ENEMY:
                            audio->play("HURT");
                            break;
                        case ECS::EntityType::PLAYER:
                            audio->play("HURT_JESS");
                            break;
                        default:
                            break;
                        }
                    }

                    if (((health.health) -= health.damage) <= 0)
                    {
                        if (audio)
                        {
                            switch (e->getType())
                            {
                            case ECS::EntityType::ENEMY:
                                audio->play("DIE");
                                break;
                            case ECS::EntityType::PLAYER:
                                audio->play("DIE_JESS");
                                break;
                            default:
                                break;
                            }
                        }
                        e->mark4destruction();
                    }
                }
                else
                {
                    if (health.initInmunity)
                    {
                        health.mStartTime = std::chrono::system_clock::now();
                        health.initInmunity = false;

                        if (audio)
                        {
                            switch (e->getType())
                            {
                            case ECS::EntityType::ENEMY:
                                audio->play("HURT");
                                break;
                            case ECS::EntityType::PLAYER:
                                audio->play("HURT");
                                break;
                            default:
                                break;
                            }
                        }

                        // TODO critico por porcentaje
                        if ((((health.health)) -= health.damage) <= 0)
                        {
                            
                            e->mark4destruction();
                        }
                    }
                    else
                    {
                        health.mDeltaTime = std::chrono::system_clock::now() - health.mStartTime;
                        // std::cout << "ELSE tiempo 2: " << health.mDeltaTime << "\n";
                        // std::cout << "ELSE count: " << health.mDeltaTime.count() << "\n";
                        if (health.mDeltaTime.count() >= health.inmunityTime)
                        {
                            health.damaged = false; // std::cout << "Ha pasado el tiempo y puede volver a perder vida\n";
                        }
                    }
                }
            }
        }
    }
}