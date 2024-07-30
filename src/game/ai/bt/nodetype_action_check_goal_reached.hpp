#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
// cmp
// #include <game/cmp/renderComponent.hpp>
// #include <game/cmp/perceptionComponent.hpp>
// #include <game/cmp/healthComponent.hpp>
#include <game/ai/pf/pathFollowingSys.hpp>
// lib
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

struct BTactionCheckGoalReached : BTnode{
    BTactionCheckGoalReached(){}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        // std::cout<< "********** check goal reached" << std::endl;

        auto pc = etcx.ent.getComponent<PathComponent>();
        auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 4;

        if(!pc->patrolInitialized){
            pfsys.setPatrolMomia(*pc, etcx.phy, *ai);
        }

        if(pc->currentGoal == nullptr){
            // std::cout<< "-- FAIL LEAVING" << std::endl; 
            return BTnodeStatus::fail;
        }

        // auto ai = etcx.ent.getComponent<AIComponent>();
        // if(ai->onPatrol){
            // std::cout<< "-- on patrol" << std::endl;
        // }else{ std::cout<< "-- NOT on patrol" << std::endl; }


        /////
        
        /////


        float dist = ((etcx.phy.position.x - pc->currentGoal->Xcoord)*(etcx.phy.position.x - pc->currentGoal->Xcoord)) + ((etcx.phy.position.z - pc->currentGoal->Zcoord)*(etcx.phy.position.z - pc->currentGoal->Zcoord));
        // std::cout<< "dist: " << dist << std::endl;
        if(dist <= waypointArriveRadius ){
            pc->currentGoal->visited = true;
            // std::cout<< "reached goal: " << pc->currentGoal->id << std::endl;
            return BTnodeStatus::success;
        }
        // std::cout<< "not reached goal " << pc->currentGoal->id << std::endl;
        return BTnodeStatus::fail;
    }

    private:
        PathfollowingSys pfsys;
        float waypointArriveRadius { 0.5f };
};