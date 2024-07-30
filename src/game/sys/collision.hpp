#pragma once
// libs
#include <cstdint>
#include <vector>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}
struct ColliderComponent;
struct PhysicsComponent;
struct BoundingBox_t;
struct worldBodyComponent;

struct CollisionSystem
{
    void update(ECS::EntityManager &em);
    void solveCollisionPlayer(ECS::EntityManager &em, ECS::Entity &ent2, PhysicsComponent& wb2);
    void solveNoCollisionPlayer(ECS::EntityManager &em, ECS::Entity &ent2);
    void solveCollision(ECS::EntityManager &em, ECS::Entity &ent1, ECS::Entity &ent2, PhysicsComponent& wb1, PhysicsComponent& wb2);
    void solveNoCollision(ECS::EntityManager &em, ECS::Entity &ent1, ECS::Entity &ent2);

    private:
    // std::vector<ECS::EntityType> no_collision_types;
    bool inCollisionObject{false};
};