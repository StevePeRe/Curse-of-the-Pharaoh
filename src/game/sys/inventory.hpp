#pragma once
// util
#include <ecs/util/globals.hpp>

namespace ECS
{
    struct EntityManager;
    struct Entity;
}

struct InventorySys
{
    explicit InventorySys() = default;

    void update(ECS::EntityManager &em);
    void openDoor(ECS::EntityManager &em, ECS::EntityTAG keyTag);
    ECS::Entity *doorCollision(ECS::EntityManager &em);
    void switchObjects(ECS::EntityManager &em, ECS::Entity &player, ECS::EntityTAG keyTag);

    private:
};
