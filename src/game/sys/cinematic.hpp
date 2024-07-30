#pragma once
// libs
#include <cstdint>
// #include <util/typealiases.hpp>

namespace ECS
{
    struct EntityManager;
}

struct CinematicSystem
{
    explicit CinematicSystem() = default;

    void update(ECS::EntityManager &em);

private:
};