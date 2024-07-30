#pragma once
// libs
#include <ecs/util/globals.hpp>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}
/* struct PhysicsComponent; */

struct RaycastSystem
{
    explicit RaycastSystem() = default;

    void update(ECS::EntityManager &em);

private:
};