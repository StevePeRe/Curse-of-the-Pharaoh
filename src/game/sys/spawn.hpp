#pragma once

namespace ECS
{
    struct Entity;
    struct EntityManager;
}

struct SpawnSystem
{
    explicit SpawnSystem() = default;

    void update(ECS::EntityManager &em);

    private:
};