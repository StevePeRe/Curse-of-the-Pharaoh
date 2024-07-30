#pragma once
// trigger
#include <game/man/puzzle/puzzle.hpp>
// libs
#include <array>
#include <stdint.h>

namespace ECS{
    struct EntityManager;
    struct Entity;
}

struct PuzzleComponent;
struct GameObjectFactory;
struct GraphicEngine;
struct AudioEngine;

struct PuzzleBotones : Puzzle
{
    explicit PuzzleBotones() = default;

    void handle(ECS::EntityManager &em, GameObjectFactory &GOF, GraphicEngine &ge, AudioEngine &au) override;
    bool getIsActive(           ) override { return isActive; }
    void setIsActive(bool active) override{ isActive = active; }
    bool getIsCompleted(           ) override { return isCompleted; }
    void setIsCompleted(bool active) override{ isCompleted = active; }

    void solvePuzzleCollision(ECS::EntityManager &em, PuzzleComponent &puzz, ECS::Entity &e_puzz);

    private:
    bool isActive { false };
    bool isCompleted { false };

    uint16_t activatedB{0};
};