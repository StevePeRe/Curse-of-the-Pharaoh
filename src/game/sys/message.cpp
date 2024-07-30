#include <game/sys/message.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/messageComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/inputComponent.hpp>
#include <game/cmp/HUD/HUDComponent.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <cstdint>
#include <iostream>
// sistema de colision con mensajes con el player
// un poco lioso pero funciona bien

void MessageSystem::update(ECS::EntityManager &em)
{
    // obtengo el HUD
	auto& HUD = em.getSingletonComponentEM<HUDComponent>();
    auto& messages = em.getComponents<MessageComponent>();
    auto *player = em.getPlayer();
    uint16_t cont_messages = 0;

    for (std::size_t i = 0; i < messages.size(); i++)
    {
        auto &message = messages[i];

        auto *e_message = em.getEntityByID(message.getEntityID());

        if (player && e_message && player != e_message)
        {
            auto *messageBody = e_message->getComponent<bodyComponent>();
            auto *messagePhy  = e_message->getComponent<PhysicsComponent>();
            auto *playerBody  = player->getComponent<bodyComponent>();
            auto *playerPhy   = player->getComponent<PhysicsComponent>();
            /* auto *playerInput = player->getComponent<InputComponent>(); */

            if (playerPhy && messagePhy && playerBody && messageBody)
            {
                if (playerBody->collisionAABB.checkObjectCollision(*playerBody, *messageBody, *playerPhy, *messagePhy))
                {
                        /* if(playerInput){
                            if(playerInput->interaction){
                                message.showMessage = true;
                            }else if(playerInput->message_erase) {
                                message.showMessage = false;
                            }
                        } 
                        if(message.showMessage){*/
                            /* HUD.setMessage(message.message);
                            HUD.showMessage(); */
                        /* } else{
                            HUD.clearMessage();
                        } */
                    if(message.justUsePopUpE){
                        HUD.setInteractMessage(message.messageUse);
                        HUD.canInteractUseE(true);// cuando colisiona con el cuadrado de usar, señala para que lo leas
                    }
                    
                    if(message.justUseMessages) {
                        // mensajes normales de dialogo
                        HUD.setMessage(message.message);
                        HUD.showMessage();
                    }
                    cont_messages = 0;
                }
                else
                {
                    cont_messages++;
                    if(cont_messages >= messages.size()) {
                        HUD.canInteractUseE(false);
                        HUD.clearMessage();
                        /* message.showMessage = false; */
                    }
                    message.showMessage = false;
                    // solveNoCollision(em, *player, *e_message);
                }
            }
        }
    }

    

}

/* void MessageSystem::solveNoCollision(ECS::EntityManager &, ECS::Entity &, ECS::Entity &)
{
}

void MessageSystem::solveCollision(ECS::EntityManager &, ECS::Entity &, ECS::Entity &, PhysicsComponent &, PhysicsComponent &)
{
} */
