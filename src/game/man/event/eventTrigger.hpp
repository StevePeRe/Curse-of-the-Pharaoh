#pragma once
// libs
#include <chrono>

namespace ECS {
    struct EntityManager;
}

struct GraphicEngine;
struct AudioEngine;

struct eventTrigger
{
    virtual ~eventTrigger() = default;
    virtual void handle(ECS::EntityManager &em, GraphicEngine &GE, AudioEngine &audio)     = 0;
};