#include <game/sys/behaviour.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/shotBehaviourComponent.hpp>
#include <game/cmp/audioComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
// factories
#include <game/factories/gameobjectfactory.hpp>
// audio
#include <engines/audio/AudioEngine.hpp>
// util
#include <ecs/util/globals.hpp>

// // triggers
// #include <game/events/ChangeColor.hpp>

// Maneja los disparos de las entidades
void BehaviourSystem::update(ECS::EntityManager &em, [[maybe_unused]] AudioEngine &audio, GameObjectFactory &GOF)
{
    for (auto &behaviour : em.getComponents<ShotBehaviourComponent>())
    {
        auto *e = em.getEntityByID(behaviour.getEntityID());
        if (e)
        {
            auto *audio = e->getComponent<AudioComponent>();
            auto *phy = e->getComponent<PhysicsComponent>();
            if (phy)
            {
                if(audio){
                    switch (behaviour.type)
                    {
                    // entrara el objeto entidad que ha sido disparado para destruirse despues de un tiempo
                    case ECS::BehaviourType::Pistol:
                        // disparo la bala
                        if (behaviour.state == ECS::BehaviourState::SHOTTING)
                        {
                            audio->play("GUN");
                            // audio.createInstance("gun_shot");
                            //  behaviour_shot(*e, em, GOF);
                            // se crea en la pos del que la genera
                            GOF.createShot(phy->position.x, phy->position.y, phy->position.z, 0.15f, 0.15f, 0.15f, ECS::BehaviourState::DestroyP, 15, 170, phy->forceDirection);
                            // audio.playSound();
                        }

                        break;
                    case ECS::BehaviourType::ShotGun:
                        if (behaviour.state == ECS::BehaviourState::SHOTTING)
                        {
                            /* phy->ownForces = -(phy->forceDirection * 4.f); */
                            audio->play("GUN");
                            //  tendria que crear varias balas a la vez, ya que es una escopeta
                            GOF.createShot(phy->position.x, phy->position.y, phy->position.z, 0.2f, 0.2f, 0.2f, ECS::BehaviourState::DestroyP, 45, 45, phy->forceDirection);
                            std::cout << "uso la escopeta\n";
                        }
                        break;
                    // case ECS::BehaviourType::ShotGun:
                    //     // llamo varias veces a la bala hasta que se destruye
                    //     behaviour_Destroyshot(*e, em, behaviour.counter, behaviour.initial_count);
                    //     break;
                    default:
                        break;
                    }
                }

                // solo tendran DESTROY los proyectiles para destruirse en su tiempo de existencia
                switch (behaviour.state)
                {
                case ECS::BehaviourState::DestroyP:
                    ShotBehaviourUpdates(*phy);
                    behaviour_Destroyshot(*e, em, behaviour.counter, behaviour.initial_count);
                    break;
                case ECS::BehaviourState::DestroyD:
                    ShotBehaviourUpdates(*phy);
                    behaviour_Destroyshot(*e, em, behaviour.counter, behaviour.initial_count);
                    break;
                case ECS::BehaviourState::DestroySG:
                    ShotBehaviourUpdates(*phy);
                    behaviour_Destroyshot(*e, em, behaviour.counter, behaviour.initial_count);
                    break;
                case ECS::BehaviourState::SHOTTING:
                    break;
                case ECS::BehaviourState::IDLEB_S:
                    break;
                }
            }
        }
    }
}

// se destruye para cualquier shot en el tiempo que esta definido
void BehaviourSystem::behaviour_Destroyshot(ECS::Entity &e, ECS::EntityManager &, uint32_t &counter, uint32_t i_count)
{
    // std::cout << "counter: " << counter << "\n";
    if (counter-- == 0)
    {
        e.mark4destruction();
        // reinicio el contador
        counter = i_count;
    }
}

void BehaviourSystem::ShotBehaviourUpdates(PhysicsComponent &phy)
{
    phy.ownForces.x += phy.forceDirection.x * 2000.f;
    phy.ownForces.z += phy.forceDirection.z * 2000.f;
}