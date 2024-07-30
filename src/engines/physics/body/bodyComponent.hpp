#pragma once

// cmp
#include <ecs/cmp/component.hpp>
#include <engines/physics/body/collider/AABB.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <vector>
#include <cstdint>

// struct AABB;

struct BoundingBox_PE
{
    float xMin{0}, yMin{0}, zMin{0};
    float xMax{0}, yMax{0}, zMax{0};
};

struct bodyComponent : ECS::Component
{
    explicit bodyComponent(std::size_t eID)
        : ECS::Component(eID){};

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(13);
    }

    // colision
    bool canCollide{true}; // detectara colision
    bool collider{true}; // no habra overlap

    /* RigidBody body{}; */
    BoundingBox_PE bBox_{};
    AABB collisionAABB{};
    
};

