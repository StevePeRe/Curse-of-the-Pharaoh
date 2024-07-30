#include <game/sys/puzzle.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// audio
#include <engines/audio/AudioEngine.hpp>
// factories
#include <game/factories/gameobjectfactory.hpp>

void PuzzleSystem::updatePuzzles(ECS::EntityManager &entityMan, GameObjectFactory &GOF, GraphicEngine &ge, AudioEngine &au)
{
    for (auto &puzzle : *puzzleManager)
    {
        if(puzzle.second.get()){
            if(puzzle.second.get()->getIsActive()) {
                puzzle.second.get()->handle(entityMan, GOF, ge, au);
            }
            if(puzzle.second.get()->getIsCompleted()) {
                    puzzleManager->erasePuzzle(puzzle.first);
                    break;
            }
        }
    }
}