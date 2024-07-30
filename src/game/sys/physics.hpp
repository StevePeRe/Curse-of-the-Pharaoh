#pragma once
#include <ecs/util/globals.hpp>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}
struct PhysicsComponent;

struct PhysicsSystem
{
    explicit PhysicsSystem() = default;

    void update(ECS::EntityManager &em, float deltaTime);

private:

};