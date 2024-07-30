#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
#include <game/factories/gameobjectfactory.hpp>
#include <iostream>

struct BTactionAttackFar : BTnode{
    BTactionAttackFar() {}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        // std::cout<< "attack far" << std::endl;

        auto current_time = std::chrono::steady_clock::now();

        [[maybe_unused]]auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 3;
        [[maybe_unused]]float deltaT = dt;

        ECS::Entity* player = etcx.entman.getPlayer();

        if((current_time - last_attack) >= attack_wait){
            etcx.GOF.createEnemyArrow(etcx.phy.position.x, etcx.phy.position.z, player->getComponent<PhysicsComponent>()->position.x, player->getComponent<PhysicsComponent>()->position.z, {1.0f,0.0f,0.0f});
            last_attack = current_time;
        }

        return BTnodeStatus::success;
    }

    private:
        std::chrono::steady_clock::time_point last_attack;
        const std::chrono::milliseconds attack_wait{3000};
};