#pragma once
#include "node.hpp"
// cmp
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// lib
#include <iostream>
#include <ecs/util/globals.hpp>

struct BTactionCheckNextToJes : BTnode{
    BTactionCheckNextToJes(){}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        // std::cout << "CHECK NEXT TO JES" << std::endl;
        [[maybe_unused]]float deltaT = dt;

        auto ai = etcx.ent.getComponent<AIComponent>();
        bool tf;
        tf = check(*ai, etcx);
        if(tf){
             return BTnodeStatus::success; }
        else { return BTnodeStatus::fail; }
        return BTnodeStatus::running;
    }

    // para que deje de moverse la ia al llegar a Jess
    bool check(AIComponent& ai, EntityContext& etcx){
        bool check = false;

        ECS::Entity* player = etcx.entman.getPlayer();
        const auto &playerPhy = player->getComponent<PhysicsComponent>();
        
        if(std::abs(playerPhy->position.x - etcx.phy.position.x) <= ai.arrivalRadius && std::abs(playerPhy->position.z - etcx.phy.position.z) <= ai.arrivalRadius && std::abs(playerPhy->position.y - etcx.phy.position.y) <= ai.maxYDifference){
            ai.tactive = true;
            ai.tx = playerPhy->position.x;
            ai.tz = playerPhy->position.z;
            ai.vX = 0.0f;
            ai.vZ = 0.0f;
            /* std::cout << "estoy al lado del jugador!!" << std::endl; */
            check = true;
        }
        else{
            check = false;
        }
        return check;
    }

    private:
};