// raiz
#include <game/puzzles/puzzlePuente.hpp>
// manager
#include <ecs/man/entitymanager.hpp>
#include <game/man/event/eventManager.hpp>
// cmp
#include <game/cmp/puzzleComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/renderComponent.hpp>
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

void PuzzlePuenteNivel1::handle(ECS::EntityManager &em, GameObjectFactory &GOF, GraphicEngine &ge, AudioEngine &audio)
{
    /* auto *player = em.getPlayer(); */
    auto &puzzle = em.getComponents<PuzzleComponent>();
    auto &eventM = em.getSingletonComponentEM<EventManager>();
    /* auto &bodies = em.getComponents<bodyComponent>(); */
    // TODO EL MUNDO CON LOS PUZZLECompont
    // luego hacelro con el getEntirdyType
    /* std::cout << "entro en puzzle puente\n"; */
    for (std::size_t i = 0; i < puzzle.size(); i++)
    {
        auto &puzzleCmp = puzzle[i];
        auto *e_puzzle = em.getEntityByID(puzzleCmp.getEntityID());
        /* std::cout << "entro en primera parte\n"; */
        if (e_puzzle && puzzleCmp.puzzle_type == ECS::PUZZLE_TYPE::PUZ_1)
        {
            /* std::cout << "entro en segunda parte\n"; */
            auto *e = em.getEntityByType(ECS::EntityType::BULLET);
            if (e)
            {
                auto *bulletPhy = e->getComponent<PhysicsComponent>();
                auto *bulletBody = e->getComponent<bodyComponent>();
                auto *puzzlePhy = e_puzzle->getComponent<PhysicsComponent>();
                auto *puzzleBody = e_puzzle->getComponent<bodyComponent>();
                if (bulletPhy && bulletBody && puzzlePhy && puzzleBody)
                {
                    if (puzzleBody->collisionAABB.checkObjectCollision(*puzzleBody, *bulletBody, *puzzlePhy, *bulletPhy))
                    {
                        GOF.createSpawnFloor(28.485f, -0.009104f, -52.98f, 5.f, 0.5f, 11.6f, {0.647f, 0.165f, 0.165f}, ECS::EntityType::SUELO, "./media/models/O_Puente.obj", "./media/textures/prueba2_puente.png", {0.0f, 0.0f, 0.0f});
                        isCompleted = true;
                        eventM.addEventType(EventMask::PZ_COMPLETED);
                        e->mark4destruction();
                        break;
                    }
                }
            }
        }
    }
}

void PuzzlePuenteNivel1::solvePuzzleCollision(ECS::EntityManager &, PuzzleComponent &, ECS::Entity &)
{
}