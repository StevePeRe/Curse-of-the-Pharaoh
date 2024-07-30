#pragma once
// libs
#include <cstdint>
// #include <util/typealiases.hpp>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}

struct GameObjectFactory;
struct AudioEngine;
struct PhysicsComponent;

struct BehaviourSystem
{
    explicit BehaviourSystem() = default;

    void update(ECS::EntityManager &em, AudioEngine &audio, GameObjectFactory& GOF);

    void behaviour_shot(ECS::Entity &e, ECS::EntityManager &em, GameObjectFactory& GOF);
    void behaviour_Destroyshot(ECS::Entity &e, ECS::EntityManager &em, uint32_t &counter, uint32_t i_count);
    void ShotBehaviourUpdates(PhysicsComponent &phy);
private:
};