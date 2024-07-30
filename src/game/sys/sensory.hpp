#pragma once

namespace ECS{
    struct EntityManager;
}

struct PhysicsComponent;

struct SensorySystem
{
    explicit SensorySystem() = default;
    void update(ECS::EntityManager &entityMan);

private:
    
};