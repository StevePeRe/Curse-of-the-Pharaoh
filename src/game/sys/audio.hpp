#pragma once
#include <ecs/util/globals.hpp>

namespace ECS
{
    struct EntityManager;
}

struct AudioEngine;
struct TNode;

struct AudioSystem
{
    explicit AudioSystem() = default;

    // ni idea de donde pilla raylib para el Vector3 xd
    bool update(ECS::EntityManager &g, AudioEngine &ae, TNode *currentCamera);

private:
    TNode *lastCameraActive = nullptr;
};