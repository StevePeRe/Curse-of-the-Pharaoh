// raiz
#include <game/puzzles/puzzleBotones.hpp>
// manager
#include <ecs/man/entitymanager.hpp>
#include <game/man/event/eventManager.hpp>
// factories
#include <game/factories/gameobjectfactory.hpp>
// cmp
#include <game/cmp/puzzleComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/inputComponent.hpp>
/* #include <game/ai/bt/createTrees.hpp> */
// audio
#include <engines/audio/AudioEngine.hpp>
// triggers
#include <game/events/PuzzleCinematic.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <iostream>
// graphic
#include <engines/graphic/GraphicEngine.hpp>

void PuzzleBotones::handle(ECS::EntityManager &em, GameObjectFactory &GOF, GraphicEngine &ge, AudioEngine &au)
{
    auto *player = em.getPlayer();
    if(!player) return;

    auto *playerInvent = player->getComponent<InventoryComponent>();
    auto *playerInput  = player->getComponent<InputComponent>();
    auto &puzzle = em.getComponents<PuzzleComponent>();
    auto &eventM = em.getSingletonComponentEM<EventManager>();

    for (std::size_t i = 0; i < puzzle.size(); i++)
    {
        auto &puzzleCmp = puzzle[i];
        auto *e_puzzle = em.getEntityByID(puzzleCmp.getEntityID());
        if (e_puzzle && puzzleCmp.puzzle_type == ECS::PUZZLE_TYPE::PUZ_2)
        {
            /* std::cout << "entro en segunda parte\n"; */
            auto *playerPhy    = player->getComponent<PhysicsComponent>();
            auto *playerBody   = player->getComponent<bodyComponent>();
            auto *puzzlePhy    = e_puzzle->getComponent<PhysicsComponent>();
            auto *puzzleBody   = e_puzzle->getComponent<bodyComponent>();

            if(playerPhy && playerBody && puzzlePhy && puzzleBody){
                if (puzzleBody->collisionAABB.checkObjectCollision(*puzzleBody, *playerBody, *puzzlePhy, *playerPhy)) {
                    if(playerInput && playerInput->interaction){
                        au.createInstance("SWITCH_OFF", "Efectos/switch_off")->Play();
                        activatedB++;
                        e_puzzle->mark4destruction(); // borro el switch para que no lo vuelva a activar
                    }
                }
            }
        }
    }

    if(activatedB == 4 && playerInvent){
        std::cout << "completado\n";
        eventM.addEventType(EventMask::PZ_COMPLETED);
        isCompleted = true;
        eventM.newTriggerEvent(CinematicEvent{});
        GOF.createKey(-41.76f, 10.05237102508545f, -92.52f, 0.5296859860420227f, 0.16593800336122513f, 0.8787630319595337f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, {1.570796251296997f, -0.0f, 0.0f}, "./media/models/L_Llave.obj", "./media/textures/llave.png", ECS::EntityTAG::KEY_1);
        playerInput->blockInput = true;
    }
}

void PuzzleBotones::solvePuzzleCollision(ECS::EntityManager &, PuzzleComponent &, ECS::Entity &)
{
    
}