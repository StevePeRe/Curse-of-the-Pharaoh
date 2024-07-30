#pragma once
#include <ecs/util/globals.hpp>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}
/* struct PhysicsComponent; */

struct PowerUpSystem
{
    explicit PowerUpSystem() = default;

    void update(ECS::EntityManager &em);

private:

};