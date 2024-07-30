#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
#include <game/cmp/aiComponent.hpp>
#include <ecs/cmp/entity.hpp>
#include <ecs/man/entitymanager.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <engines/physics/body/bodyComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <ecs/util/globals.hpp>
#include <iostream>
#include <game/ai/sb/stbeh.hpp>

struct BTactionCheckJesClose : BTnode{
    BTactionCheckJesClose() {}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        // std::cout << "entro en checkjesclose" << std::endl;

        // return BTnodeStatus::fail;

        auto ai = etcx.ent.getComponent<AIComponent>();
        //BlackBoardComponent& bb = etcx.entman.getSingletonComponentEM<BlackBoardComponent>(); //para escarabajos

        if((ai->enemyType!=2 && stbeh.perception(*ai, dt))/*|| (ai->enemyType==2 && stbeh.perceptionBB(bb, *ai, dt))*/){ //comentado pq los escarabajos no tienen checkClose rn
            bool tf = check(*ai, etcx);
            if(tf){ /*std::cout << "jes is CLOSE" << std::endl;*/ return BTnodeStatus::success; }
            else { return BTnodeStatus::fail; }
        }
        else { return BTnodeStatus::fail; }
  
        return BTnodeStatus::running; 
    }

    //bool check(AIComponent& ai, EntityContext& etcx){
    //    ECS::Entity* player = etcx.entman.getPlayer();
    //    const auto &playerPhy = player->getComponent<PhysicsComponent>();
    //    if(std::abs(playerPhy->position.x - etcx.phy.position.x) <= ai.noticeRadius && std::abs(playerPhy->position.z - etcx.phy.position.z) <= ai.noticeRadius && std::abs(playerPhy->position.y - etcx.phy.position.y) <= ai.maxYDifference){
    //        ai.tactive = true;
    //        ai.tx = playerPhy->position.x;
    //        ai.tz = playerPhy->position.z;
    //
    //        return true;
    //    }else{
    //        return false;
    //    }
    //}

    bool check(AIComponent &ai, EntityContext &etcx)
    {
        bool check = false;
        ECS::Entity* player = etcx.entman.getPlayer();

        auto *playerPhy = player->getComponent<PhysicsComponent>();
        
        // visual
        auto *percIA = etcx.ent.getComponent<PerceptionComponent>();

        if(percIA && playerPhy) {
            if(percIA->seen) {
                std::cout << "entro en IA lo veo check close AAAAAAAAA\n";
                ai.tactive = true;
                ai.tx = playerPhy->position.x;
                ai.tz = playerPhy->position.z;
                check = true;
            }
        }

        return check;
    }

    private:
        StBeh stbeh;
};