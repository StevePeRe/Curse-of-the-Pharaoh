// raiz
#include <game/puzzles/puzzlePilares.hpp>
// manager
#include <ecs/man/entitymanager.hpp>
#include <game/man/event/eventManager.hpp>
// cmp
#include <game/cmp/puzzleComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/inputComponent.hpp>
#include <game/cmp/HUD/HUDComponent.hpp>
// factories
#include <game/factories/gameobjectfactory.hpp>
// audio
#include <engines/audio/AudioEngine.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <iostream>
// graphic
#include <engines/graphic/GraphicEngine.hpp>
#include <engines/graphic/T_EMesh.hpp>

void PuzzlePilares::handle(ECS::EntityManager &em, GameObjectFactory &, GraphicEngine &ge, AudioEngine &audio)
{
    auto *player = em.getPlayer();
    auto &puzzle = em.getComponents<PuzzleComponent>();

    // SOLO COMPRUEBO LAS ENTIDADES QUE TENGAN PUZZLECOMPONENT
    for (std::size_t i = 0; i < puzzle.size(); i++)
    {
        auto &puzzleCmp = puzzle[i];
        auto *e_puzzle = em.getEntityByID(puzzleCmp.getEntityID());
        if (player && e_puzzle && puzzleCmp.puzzle_type == ECS::PUZZLE_TYPE::PUZ_1)
        {
            auto *playerBody = player->getComponent<bodyComponent>();
            auto *playerPhy = player->getComponent<PhysicsComponent>();
            auto *playerInp = player->getComponent<InputComponent>();    
            auto *puzzlePhy = e_puzzle->getComponent<PhysicsComponent>();
            auto *puzzleBody = e_puzzle->getComponent<bodyComponent>();
            auto *puzzleRend = e_puzzle->getComponent<RenderComponent>();

            if (playerBody && playerPhy && puzzlePhy && puzzleBody && puzzleRend)
            {
                if (playerBody->collisionAABB.checkObjectCollision(*playerBody, *puzzleBody, *playerPhy, *puzzlePhy))
                {
                    if (playerInp->interaction)
                    {
                        solvePuzzleCollision(em, puzzleCmp, *e_puzzle, ge, audio);
                    }
                }
            }
        }
    }
}

void PuzzlePilares::solvePuzzleCollision(ECS::EntityManager &em, PuzzleComponent &puzz, ECS::Entity &, GraphicEngine &ge, AudioEngine &audio)
{
    auto *player = em.getPlayer();
    auto *puzzle = em.getEntityByID(puzz.getEntityID());
    auto &HUD = em.getSingletonComponentEM<HUDComponent>();
    auto &eventM = em.getSingletonComponentEM<EventManager>();

    if (player && puzzle)
    {
        auto *playerInv = player->getComponent<InventoryComponent>();
        auto *puzzleRend = puzzle->getComponent<RenderComponent>();

        // nivel que ya estaba implementacion sencilla,cabair a los nuevos
        switch (puzz.puzzle_object)
        {
        case ECS::PUZZLE_TYPE::INTERACTION:
            break;
        case ECS::PUZZLE_TYPE::PILARES:
            // en collSys ve si esta activo o no, aqui nada
            break;
        case ECS::PUZZLE_TYPE::PILARES_1:
            if (!pillar1Active)
            {
                guessedOrder[contPillars] = 1;
                contPillars++;
                pillar1Active = true;
                puzzleRend->color = {1.0f, 1.0f, 0.0f};
                ge.addTexture("./media/textures/acertijo-hombreA.png", puzzleRend->node);
                audio.createInstance("SWITCH_ON", "Efectos/switch_on")->Play();
            }
            break;
        case ECS::PUZZLE_TYPE::PILARES_2:
            if (!pillar2Active)
            {
                guessedOrder[contPillars] = 2;
                contPillars++;
                pillar2Active = true;
                puzzleRend->color = {1.0f, 1.0f, 0.0f};
                ge.addTexture("./media/textures/musicoA.png", puzzleRend->node);
                audio.createInstance("SWITCH_ON", "Efectos/switch_on")->Play();
            }
            break;
        case ECS::PUZZLE_TYPE::PILARES_3:
            if (!pillar3Active)
            {
                guessedOrder[contPillars] = 3;
                contPillars++;
                pillar3Active = true;
                puzzleRend->color = {1.0f, 1.0f, 0.0f};
                ge.addTexture("./media/textures/acertijo-hombre-bestiaA.png", puzzleRend->node);
                audio.createInstance("SWITCH_ON", "Efectos/switch_on")->Play();
            }
            break;
        case ECS::PUZZLE_TYPE::PILARES_4:
            if (!pillar4Active)
            {
                guessedOrder[contPillars] = 4;
                contPillars++;
                pillar4Active = true;
                puzzleRend->color = {1.0f, 1.0f, 0.0f};
                ge.addTexture("./media/textures/musico_bestiaA.png", puzzleRend->node);
                audio.createInstance("SWITCH_ON", "Efectos/switch_on")->Play();
            }
            break;
        }

        if (contPillars >= 4)
        {
            contPillars = 0;
            // si esta bien
            for (size_t i = 0; i < guessedOrder.size(); i++)
            {
                if (guessedOrder[i] == correctOrder[i])
                {
                    contPillars++;
                }
                else
                {
                    IsCompletedPillars = false;
                    break;
                }
            }

            if (contPillars >= 4)
            {
                isCompleted = true;
                HUD.setQuickMessage("Anda una llave! ¿Para que servira?");
                HUD.showQuickMessage();
                playerInv->addElement(ECS::EntityTAG::KEY_2);
                eventM.addEventType(EventMask::PZ_COMPLETED);
            }
            else
            {
                // He probado arriba lo de desactivar pero necesita iteractuar para desactivar entonces lo hago aqui
                for (auto &puzz_ : em.getComponents<PuzzleComponent>())
                {
                    auto *puzzle_ = em.getEntityByID(puzz_.getEntityID());
                    auto *puzzQuitar = puzzle_->getComponent<RenderComponent>();
                    switch (puzz_.puzzle_object)
                    {
                    case ECS::PUZZLE_TYPE::INTERACTION:
                        break;
                    case ECS::PUZZLE_TYPE::PILARES:
                        // en collSys ve si esta activo o no, aqui nada
                        break;
                    case ECS::PUZZLE_TYPE::PILARES_1:
                        ge.addTexture("./media/textures/acertijo-hombre.png", puzzQuitar->node);
                        break;
                    case ECS::PUZZLE_TYPE::PILARES_2:
                        ge.addTexture("./media/textures/musico.png", puzzQuitar->node);
                        break;
                    case ECS::PUZZLE_TYPE::PILARES_3:
                        ge.addTexture("./media/textures/acertijo-hombre-bestia.png", puzzQuitar->node);
                        break;
                    case ECS::PUZZLE_TYPE::PILARES_4:
                        ge.addTexture("./media/textures/musico_bestia.png", puzzQuitar->node);
                        break;
                    }
                }
                contPillars = 0;
                pillar1Active = pillar2Active = pillar3Active = pillar4Active = false;
                HUD.setQuickMessage("No ha pasado nada, parece que no era el orden correcto.");
                HUD.showQuickMessage();
            }
        }
    }
}