#pragma once
// util
#include <ecs/util/globals.hpp>
//cmp
#include <game/ai/bb/blackboardComponent.hpp>
// libs
// #include <raylib.h>
#include <chrono>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}

struct AIComponent;
struct PhysicsComponent;
struct AnimationComponent;

struct Steer{
        float linearVX { 0.0f };
        float linearVZ { 0.0f };
};

struct StBeh{

    Steer arrive(AIComponent& ai, PhysicsComponent& phy);
    Steer seek(AIComponent& ai, PhysicsComponent& phy, AnimationComponent &anim);
    Steer idle(AIComponent& ai, PhysicsComponent& phy, AnimationComponent &anim);
    Steer evade(AIComponent& ai, PhysicsComponent& phy, Steer& st, ECS::EntityManager& em);
    Steer flock(AIComponent& ai, PhysicsComponent& phy, Steer& st, ECS::EntityManager& em);
    Steer flee(AIComponent& ai, PhysicsComponent& phy);

    bool perceptionBB(BlackBoardComponent& bb, AIComponent& ai, float);
    bool perception(AIComponent& ai, float);

    float angleBetweenVectors(float, float, float, float);
    std::array<float, 2> bisectriz(float, float, float, float);
    std::array<float, 2> centroid(const std::vector<PhysicsComponent>&);

    private:
        std::chrono::steady_clock::time_point last_idle_move;
        const std::chrono::milliseconds idle_move_wait{2000};

};