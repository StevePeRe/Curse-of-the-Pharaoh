#pragma once
#include <cstdint>
//#include <game/cmp/aiComponent.hpp>
#include <game/factories/gameobjectfactory.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <ecs/man/entitymanager.hpp>

struct EntityContext{
    //AIComponent&        ai;
    PhysicsComponent&   phy;
    ECS::Entity&        ent;
    ECS::EntityManager& entman;
    GameObjectFactory&  GOF;
};

enum class BTnodeStatus: uint8_t{
    success,
    fail,
    running
};

struct BTnode{
    BTnode() = default;
    struct Deleter { void operator()(BTnode* n){n->~BTnode();} };

    BTnode(const BTnode&)            = delete;
    BTnode(BTnode&&)                 = delete;
    BTnode& operator=(const BTnode&) = delete;
    BTnode& operator=(BTnode&&)      = delete;

    virtual BTnodeStatus run(EntityContext& etcx, float dt) noexcept = 0;
    virtual ~BTnode() = default;
};
