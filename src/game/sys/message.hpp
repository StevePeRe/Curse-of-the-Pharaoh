#pragma once
// libs
#include <cstdint>
#include <vector>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}

struct PhysicsComponent;
struct BoundingBox_t;

struct MessageSystem
{
    void update(ECS::EntityManager &em);
    /* void solveCollision(ECS::EntityManager &em, ECS::Entity &ent1, ECS::Entity &ent2, PhysicsComponent& wb1, PhysicsComponent& wb2);
    void solveNoCollision(ECS::EntityManager &em, ECS::Entity &ent1, ECS::Entity &ent2); */

    private:
    /* bool isActive{false}; */
};