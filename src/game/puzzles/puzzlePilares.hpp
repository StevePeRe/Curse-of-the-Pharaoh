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

struct PuzzlePilares : Puzzle
{
    explicit PuzzlePilares() = default;

    void handle(ECS::EntityManager &em, GameObjectFactory &GOF, GraphicEngine &ge, AudioEngine &audio) override;
    bool getIsActive(           ) override { return isActive; }
    void setIsActive(bool active) override{ isActive = active; }
    bool getIsCompleted(           ) override { return isCompleted; }
    void setIsCompleted(bool active) override{ isCompleted = active; }

    void solvePuzzleCollision(ECS::EntityManager &em, PuzzleComponent &puzz, ECS::Entity &e_puzz, GraphicEngine &ge, AudioEngine &audio);

    private:
    bool isActive { false };
    bool isCompleted { false };

    std::array<int, 4> guessedOrder;
    std::array<int, 4> correctOrder = {1,2,3,4}; // 1,2,3,4
    uint16_t contPillars{0};
    bool pillar1Active{false}, pillar2Active{false}, pillar3Active{false}, pillar4Active{false};

    // puzzle completo
    bool IsCompletedPillars{false};
};