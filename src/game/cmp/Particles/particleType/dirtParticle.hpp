#pragma once
#include <game/cmp/Particles/particleType/particle.hpp>
// libs
#include <array>
#include <stdint.h>
namespace ECS
{
    struct EntityManager;
}

struct GameObjectFactory;

struct DirtParticle : Particle
{
    explicit DirtParticle() = default;
    void handle(ECS::EntityManager &em, GameObjectFactory &GOF) override;

    /* virtual bool getIsActive() = 0;
    virtual void setIsActive(bool active) = 0;
    virtual bool getIsCompleted() = 0;
    virtual void setIsCompleted(bool active) = 0; */

private:
// isActive es para saber si el puzle ya está activo -> se activa al colisionar
// isCompleted si al estar activo esta completo
};