#pragma once
// libs
#include <cstdint>
#include <vector>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}

struct ParticleSystem
{
    void update(ECS::EntityManager &em);

    private:
};