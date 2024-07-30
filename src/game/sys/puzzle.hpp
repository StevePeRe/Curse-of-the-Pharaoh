#pragma once
#include <game/man/puzzlemanager.hpp>

namespace ECS{
    struct EntityManager;
}

struct GameObjectFactory;
struct GraphicEngine;
struct AudioEngine;

struct PuzzleSystem
{
    explicit PuzzleSystem(PuzzleManager &puzzle) : puzzleManager(&puzzle){}
    void updatePuzzles(ECS::EntityManager &entityMan, GameObjectFactory &GOF, GraphicEngine &ge, AudioEngine &au);

    // void update();
    // void lateUpdate();

private:
// lo hago puntero para no crear una copia cuando se lon paso por el constr
    PuzzleManager *puzzleManager{nullptr};
    
};