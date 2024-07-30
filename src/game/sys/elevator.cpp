#include <game/sys/elevator.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/elevatorComponent.hpp>
#include <game/cmp/inputComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/switchComponent.hpp>
#include <game/cmp/messageComponent.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// libs
#include <cstdint>
#include <iostream>

// crear una palanca para que si sube el ascensor sin querer que podamos llamarlo de regreso

// si mas adelanta queremos poner bloques que tmb se muevan en horizontal lo hare aqui mismo, seria crear el ascensor con el sentido de recorrido que queremos que tenga
// y poner que el jugador se pegue al ascensor hasta que acabe el recorrido en vez de blquear el input, o directamente quitar el que se bloquee el input y hacer que sea mas complicado el ir en ascensro
void ElevatorSystem::update(ECS::EntityManager &em)
{
    auto *player = em.getPlayer();
    if(player){
        [[maybe_unused]]auto* phyPlayer = player->getComponent<PhysicsComponent>();
        auto& switchs = em.getComponents<SwitchComponent>();

        auto *playerInput = player->getComponent<InputComponent>();
        if(playerInput && playerInput->interaction){
            isActive = true; // controla si pulso la E o no
        }else{
            isActive = false;
        }

        switchType = ECS::SwitchType::NONE_ELEVATOR;
        for(auto& swit : switchs){
            auto* e = em.getEntityByID(swit.getEntityID());
            if(e){
                checkCollision(*player, *e); // comprubeo si hay colision entre el player y le switch
                // miro antes de activar el switch si he activado la E
                if(isActive && swit.active){
                    switchType = swit.switchType;
                }
            }
        }

        for(auto& elevator : em.getComponents<ElevatorComponent>()){
            // entrara en cada iteracion del programa al ascensor que este activo
            // std::cout << "puedo activar ascensor\n";
            auto* e = em.getEntityByID(elevator.getEntityID());
            if(e){
                checkCollision(*player, *e); // miro si hay colision entre el player y el ascensor

                auto* phy = e->getComponent<PhysicsComponent>();  
                auto* swi = e->getComponent<SwitchComponent>();  
                auto* mss = e->getComponent<MessageComponent>();  
                if(phy && mss){
                    // movebloqued tiene que ser para cada comppemonte
                    if(!elevator.moveBlocked && isActive){ // cuando colisiona con el player isActive es true
                        if(elevator.active || swi->switchType == switchType){
                            elevator.working = !elevator.working; // hacia arriba o hacia abajo
                            /* std::cout << "ee: " << elevator.working << "\n"; */
                            elevator.moveBlocked = true;
                            // playerInput->blockInput = true;
                            mss->justUsePopUpE = false;
                        }
                    }

                    if(elevator.moveBlocked){
                        switch (elevator.direction)
                        {
                        case ECS::ElevatorDirection::DIR_Y:
                            /* phy->velocity.y = 2.f; */
                            if(elevator.working){
                            // goingUp
                            /* std::cout << "altura y: " << phy->position.y << "\n"; */
                                if(phy->position.y <= elevator.end_position){
                                    mss->justUsePopUpE = false;
                                    phy->ownForces.y += 200.f;
                                }else{
                                    /* std::cout << "------------------------------------\n"; */
                                    phy->position.y = elevator.end_position;
                                    phy->ownForces.y = 0;
                                    mss->justUsePopUpE = true;
                                    elevator.moveBlocked = false;
                                }
                            }else{
                                // goingDown
                                /* std::cout << "altura y: " << phy->position.y << "\n"; */
                                if(phy->position.y >= elevator.initial_position){
                                    mss->justUsePopUpE = false;
                                    phy->ownForces.y -= 200.f;
                                }else{
                                    /* std::cout << "------------------------------------\n"; */
                                    phy->position.y = elevator.initial_position;
                                    phy->ownForces.y = 0;
                                    mss->justUsePopUpE = true;
                                    elevator.moveBlocked = false;
                                }
                            }
                            break;
                        case ECS::ElevatorDirection::DIR_Z:
                            /* phy->velocity.z = 2.f; */
                            if(elevator.working){
                            if(phy->position.z <= elevator.end_position){
                                mss->justUsePopUpE = false;
                                phy->ownForces.z += 200.f;
                            }else{
                                phy->position.y = elevator.end_position;
                                phy->ownForces.z = 0;
                                mss->justUsePopUpE = true;
                                elevator.moveBlocked = false;
                            }
                            }else{
                                if(phy->position.z >= elevator.initial_position){
                                    mss->justUsePopUpE = false;
                                    phy->ownForces.z -= 200.f;
                                }else{
                                    phy->position.y = elevator.initial_position;
                                    phy->ownForces.z = 0;
                                    mss->justUsePopUpE = true;
                                    elevator.moveBlocked = false;
                                }
                            }
                            break;
                        case ECS::ElevatorDirection::DIR_X:
                            if(elevator.working){
                                if(phy->position.x <= elevator.end_position){
                                    mss->justUsePopUpE = false;
                                    phy->ownForces.x += 200.f;
                                }else{
                                    phy->position.y = elevator.end_position;
                                    phy->ownForces.x = 0;
                                    mss->justUsePopUpE = true;
                                    elevator.moveBlocked = false;
                                }
                            }else{
                                if(phy->position.x >= elevator.initial_position){
                                    mss->justUsePopUpE = false;
                                    phy->ownForces.x -= 200.f;
                                }else{
                                    phy->position.y = elevator.initial_position;
                                    phy->ownForces.x = 0;
                                    mss->justUsePopUpE = true;
                                    elevator.moveBlocked = false;
                                }
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
}

void ElevatorSystem::checkCollision(ECS::Entity &player, ECS::Entity &cmpE)
{
    auto *cmpEPhy  = cmpE.getComponent<PhysicsComponent>();
    auto *cmpEBody = cmpE.getComponent<bodyComponent>();
    auto *cmpESwit = cmpE.getComponent<SwitchComponent>();
    auto *cmpEElev = cmpE.getComponent<ElevatorComponent>();

    auto *playerBody = player.getComponent<bodyComponent>();
    auto *playerPhy  = player.getComponent<PhysicsComponent>();

    if(cmpEPhy && cmpEBody && playerBody && playerPhy){
        if (playerBody->collisionAABB.checkObjectCollision(*playerBody, *cmpEBody, *playerPhy, *cmpEPhy))
        {
            if(cmpESwit){
                cmpESwit->active = true;
            }
            if(cmpEElev){
                cmpEElev->active = true;
            }
        } 
        else {
            if(cmpESwit){
                cmpESwit->active = false;
            }
            if(cmpEElev){
                cmpEElev->active = false;
            }
        }
    }
}