#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// utils
#include <ecs/util/globals.hpp>
// libs
////#include <raylib.h>
#include <cstdint>

struct PuzzleComponent : ECS::Component
{

    using PuzzleName = ECS::PUZZLE_TYPE;

    explicit PuzzleComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(16);
    }

    PuzzleName puzzle_type{ECS::PUZZLE_TYPE::NONE_PUZZLE}; // nombre del puzzle al que pertenece la entidad
    PuzzleName puzzle_object{ECS::PUZZLE_TYPE::NONE_PUZZLE};
};