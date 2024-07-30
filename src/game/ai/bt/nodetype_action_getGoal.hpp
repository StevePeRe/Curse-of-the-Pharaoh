#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
// cmp
#include <game/ai/pf/pathComponent.hpp>
// lib
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

struct BTactionGetGoal : BTnode{
    BTactionGetGoal(){}

    BTnodeStatus run(EntityContext& etcx, [[maybe_unused]]float dt) noexcept final{
        // std::cout<< "getgoal" << std::endl;

        auto pc = etcx.ent.getComponent<PathComponent>();

        if(!pc->patrolInitialized){
            pfsys.setPatrolMomia(*pc, etcx.phy, *etcx.ent.getComponent<AIComponent>());
        }

        auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 7;
        pc->currentGoal = nullptr;
        // Steer st;

        if(ai->onPatrol && ai->patrolInterrupted){
            // std::cout<< "patrol Interrupted" << std::endl;
            for(int i=0; i<(int)pc->patrolRouteReturn.size(); i++){
                if(!pc->patrolRouteReturn.at(i)->visited){
                    pc->currentGoal = pc->patrolRouteReturn.at(i);
                    // std::cout<< "next goal: " << pc->currentGoal->Xcoord << ", " << pc->currentGoal->Zcoord << std::endl;
                    break;
                }
            }

            if(pc->currentGoal == nullptr){
                // std::cout<< "he vuelto a la ruta patrulla" << std::endl;
                ai->patrolInterrupted = false;
                pc->currentGoal = pc->patrolRouteReturn.at(pc->patrolRouteReturn.size()-1);
                for(int i=0; i<(int)pc->patrolRouteReturn.size(); i++){
                    pc->patrolRouteReturn.at(i)->visited = false;
                }
                pc->foundGoal = false;
                pc->foundReturnGoal = false;
                pc->pathToGoal.clear();
                pc->visitedList.clear();
                pc->startCell = pc->goalCell;
                pc->goalCell = nullptr;
                pc->hasReachedStart = false;
                pc->hasReachedGoal = false;
                pc->initializedStartAndGoal = false;
                ai->onPatrol = true;
            }
        }
        else if(ai->onPatrol){ //si esta en modo patrullar
            // std::cout<< "on patrol" << std::endl;
            for(int i=0; i<(int)pc->patrolRoute.size(); i++){
                if(!pc->patrolRoute.at(i)->visited){
                    pc->currentGoal = pc->patrolRoute.at(i);
                    // std::cout<< "next goal: " << pc->currentGoal->id <<  std::endl;
                    break;
                }
            }

            if(pc->currentGoal == nullptr){
                pc->currentGoal = pc->patrolRoute.at(0);
                for(int i=0; i<(int)pc->patrolRoute.size(); i++){
                    pc->patrolRoute.at(i)->visited = false;
                }
            }
        }
        else if(!ai->onPatrol){
            bool complete = true;
            // std::cout<< "NOT on patrol" << std::endl;
            for(int i=0; i<(int)pc->pathToGoal.size(); i++){
                if(!pc->pathToGoal.at(i)->visited){
                    pc->currentGoal = pc->pathToGoal.at(i);
                    complete = false;
                    // std::cout<< "next goal: " << pc->currentGoal->Xcoord << ", " << pc->currentGoal->Zcoord << std::endl;
                    break;
                }
            }

            if(complete){ // HA LLEGADO A LA META
                // std::cout << "** META ALCANZADAAAAAAA ***" << std::endl;
                for(int i=0; i<(int)pc->pathToGoal.size(); i++){
                    pc->pathToGoal.at(i)->visited = false;
                }
                pc->foundGoal = false;
                pc->pathToGoal.clear();
                pc->visitedList.clear();
                pc->startCell = pc->goalCell;
                pc->goalCell = nullptr;
                pc->hasReachedStart = false;
                pc->hasReachedGoal = false;
                pc->initializedStartAndGoal = false;
                ai->vX = 0.0f;
                ai->vZ = 0.0f;
                ai->onPatrol = true;
                // std::cout << "** return fail ***" << std::endl;
                return BTnodeStatus::fail;
            }
        }
        
        float distanceX = (pc->currentGoal->Xcoord - etcx.phy.position.x);
        float distanceZ = (pc->currentGoal->Zcoord - etcx.phy.position.z);

        ai->vX = distanceX/5.f;
        ai->vZ = distanceZ/5.f;
        
        return BTnodeStatus::success;
    }

    private:
        PathfollowingSys pfsys;
};