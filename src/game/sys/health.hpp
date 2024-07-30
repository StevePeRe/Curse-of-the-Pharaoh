#pragma once

namespace ECS
{
    struct Entity;
    struct EntityManager;
}

struct HealthSystem
{
    explicit HealthSystem() = default;

    void update(ECS::EntityManager &em);

    private:
};