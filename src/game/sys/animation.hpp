#pragma once
#include <ecs/util/globals.hpp>

namespace ECS
{
    struct EntityManager;
}

struct GraphicEngine;


struct AnimationSystem
{
    explicit AnimationSystem() = default;

    bool update(ECS::EntityManager &g, GraphicEngine &ge, float dt);

private:
    
};