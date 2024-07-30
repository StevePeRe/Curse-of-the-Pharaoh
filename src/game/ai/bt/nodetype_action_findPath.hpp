#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
#include <game/cmp/aiComponent.hpp>
#include <ecs/cmp/entity.hpp>
#include <ecs/man/entitymanager.hpp>
#include <game/ai/pf/pathFollowingSys.hpp>
#include <game/ai/pf/pathComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <ecs/util/globals.hpp>
#include <iostream>
#include <game/ai/sb/stbeh.hpp>

struct BTactionFindPath : BTnode{
    BTactionFindPath() {}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        // std::cout << "find path" << std::endl;

        auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 5;
        // if(ai->onPatrol){
            // std::cout<< "-- fp on patrol" << std::endl;
        // }else{ std::cout<< "-- fp NOT on patrol" << std::endl; }

        //SOLO ENTRAR SI DIST ENEMIGO-PLAYER ES MAYOR QUE LA DIST ENTRE WP Y WP
        
        auto pc = etcx.ent.getComponent<PathComponent>();
        if(pc->foundGoal){ return BTnodeStatus::success; }

        pfsys.update(etcx.entman, *pc, etcx.phy, ECS::currentlevel);
        ai->onPatrol = false;

        if(pc->foundGoal){
            // std::cout << "goal found :)" << std::endl;
            pc->currentGoal = pc->pathToGoal.at(0);
            float distanceX = (pc->currentGoal->Xcoord - etcx.phy.position.x);
            float distanceZ = (pc->currentGoal->Zcoord - etcx.phy.position.z);
    
            ai->vX = distanceX/5.f;
            ai->vZ = distanceZ/5.f;
            // std::cout << "goal found :) :: " << pc->currentGoal->id << std::endl;
            ai->patrolInterrupted = true;
            return BTnodeStatus::success; 
        }
        else{
            // std::cout << "goal not yet found" << std::endl;
            return BTnodeStatus::running; 
        }
        // std::cout << "uuuuuu fantasma" << std::endl;
        return BTnodeStatus::success; 
        
    }

    private:
        PathfollowingSys pfsys;
};