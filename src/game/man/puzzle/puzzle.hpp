#pragma once

namespace ECS
{
    struct EntityManager;
}

struct GameObjectFactory;
struct GraphicEngine;
struct AudioEngine;

struct Puzzle
{
    virtual ~Puzzle() = default;
    virtual void handle(ECS::EntityManager &em, GameObjectFactory &GOF, GraphicEngine &ge, AudioEngine &au) = 0;

    virtual bool getIsActive() = 0;
    virtual void setIsActive(bool active) = 0;
    virtual bool getIsCompleted() = 0;
    virtual void setIsCompleted(bool active) = 0;

};