#pragma once
// util
#include <ecs/util/globals.hpp>
#include <game/factories/gameobjectfactory.hpp>
//cmp
#include <game/ai/bb/blackboardComponent.hpp>
// libs
//#include <raylib.h>
#include <chrono>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}

struct AIComponent;
struct PhysicsComponent;
struct GraphicEngine;

struct AISystem
{
    explicit AISystem() = default;

    // void updateOne(ECS::EntityManager &, ECS::Entity &, float);

    void update(ECS::EntityManager &em, GraphicEngine &GE, float, GameObjectFactory &GOF);

    private:
};