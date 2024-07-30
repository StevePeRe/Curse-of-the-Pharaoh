#pragma once

namespace ECS
{
    struct EntityManager;
}

struct GameObjectFactory;

struct Particle
{
    virtual ~Particle() = default;
    virtual void handle(ECS::EntityManager &em, GameObjectFactory &GOF) = 0;

private:

};