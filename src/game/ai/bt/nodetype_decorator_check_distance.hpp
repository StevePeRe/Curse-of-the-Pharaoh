#pragma once
#include "node.hpp"
// cmp
#include <game/cmp/perceptionComponent.hpp>
// libs
#include <iostream>
#include <glm/glm.hpp>

struct BTdecoratorCheckDistance : BTnode {
    BTnode* ch_nextTo;
    BTnode* ch_closeTo;
    // BTnode* ch_farFrom;

    BTdecoratorCheckDistance(BTnode* ch_nextTo, BTnode* ch_closeTo): ch_nextTo(ch_nextTo), ch_closeTo(ch_closeTo){
        //if (!ch_nextTo || !ch_closeTo || !ch_farFrom){
        //    throw std::invalid_argument("Child nodes cannot be null");
        //}
    }

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final {
        
        auto ai = etcx.ent.getComponent<AIComponent>();
        std::cout << "distace to player: " << ai->distPlayer << std::endl;
        BlackBoardComponent& bb = etcx.entman.getSingletonComponentEM<BlackBoardComponent>();
        ai->currentNode = 11;
        auto ent = etcx.entman.getPlayer();
        auto *percIA = etcx.ent.getComponent<PerceptionComponent>();
        auto phyPlayer = ent->getComponent<PhysicsComponent>();
        float distance = std::sqrt((phyPlayer->position.x - etcx.phy.position.x)*(phyPlayer->position.x - etcx.phy.position.x) + 
                                   (phyPlayer->position.z - etcx.phy.position.z)*(phyPlayer->position.z - etcx.phy.position.z) +
                                   (phyPlayer->position.y - etcx.phy.position.y)*(phyPlayer->position.y - etcx.phy.position.y));

        /* bool perceived = true; */
        //if(etcx.ent.getComponent<AIComponent>()->enemyType == 2){
        //    perceived = stbeh.perceptionBB(etcx.entman.getSingletonComponentEM<BlackBoardComponent>(), 
        //                                   *etcx.ent.getComponent<AIComponent>(), dt);
        //}
        //else{
        //    perceived = stbeh.perception(*etcx.ent.getComponent<AIComponent>(), dt);
        //}
        // DESCOMENTAR ESTO PARA ENEMIGOS NORMALES
        ///////
        if(ai->detectedPlayer || ai->enemyType ==2 && bb.tactive){
            if (distance < etcx.ent.getComponent<AIComponent>()->arrivalRadius) {
                // std::cout << "decorador distace DETECTED 1" << std::endl;
                etcx.ent.getComponent<AIComponent>()->tx = phyPlayer->position.x;
                etcx.ent.getComponent<AIComponent>()->tz = phyPlayer->position.z;
                return ch_nextTo->run(etcx, dt);
            } 
            else if(distance < mediumThreshold){
                if(ai->enemyType == 2){
                    bb.tactive = true;
                    bb.tx = phyPlayer->position.x;
                    bb.tz = phyPlayer->position.z;
                }
                // std::cout << "decorador distace DETECTED 2" << std::endl;
                etcx.ent.getComponent<AIComponent>()->tx = phyPlayer->position.x;
                etcx.ent.getComponent<AIComponent>()->tz = phyPlayer->position.z;
                return ch_closeTo->run(etcx, dt);
            }

        }
        else if(percIA && !ai->detectedPlayer) {
            if (distance < etcx.ent.getComponent<AIComponent>()->arrivalRadius && (percIA->seen || percIA->heard)) {
                std::cout << "decorador distace 1" << std::endl;
                etcx.ent.getComponent<AIComponent>()->tx = phyPlayer->position.x;
                etcx.ent.getComponent<AIComponent>()->tz = phyPlayer->position.z;
                ai->detectedPlayer = true;
                return ch_nextTo->run(etcx, dt);
            } 
            else if(distance < mediumThreshold && (percIA->seen || percIA->heard)){
                if(ai->enemyType == 2){
                    bb.tactive = true;
                    bb.tx = phyPlayer->position.x;
                    bb.tz = phyPlayer->position.z;
                }
                ai->detectedPlayer = true;
                std::cout << "decorador distace 2" << std::endl;
                etcx.ent.getComponent<AIComponent>()->tx = phyPlayer->position.x;
                etcx.ent.getComponent<AIComponent>()->tz = phyPlayer->position.z;
                // auto bt = ch_closeTo->run(etcx, dt);
                // switch(bt){
                    // case BTnodeStatus::fail: { std::cout << "findpath devuelve fail" << std::endl; }
                    // break;
                    // case BTnodeStatus::running: { std::cout << "findpath devuelve running" << std::endl; }
                    // break;
                    // case BTnodeStatus::success: { std::cout << "findpath devuelve success" << std::endl; 
                                                    // return BTnodeStatus::success;}
                    // break;
                // }
                // std::cout << "salgo del switch" << std::endl;
                return ch_closeTo->run(etcx, dt);
            }
            else{
                auto pc = etcx.ent.getComponent<PathComponent>();

                std::cout << "decorador distace fail " << std::endl;
                
                if(ai->patrolInterrupted && pc->currentGoal == nullptr && !pc->foundReturnGoal){
                    // std::cout << "PATROL INTERRUPTED" << std::endl;
                    pfsys.findReturnRoute(etcx.entman, *pc, etcx.phy, *ai, ECS::currentlevel);
                    // for(int i=0;i<(int)pc->patrolRouteReturn.size(); i++){
                        // std::cout << "return path wp: " << pc->patrolRouteReturn.at(i)->id << std::endl;
                    // }
                    pc->foundReturnGoal = true;
                    pc->currentGoal = pc->patrolRouteReturn.at(0);
                    ai->vX = (pc->currentGoal->Xcoord - etcx.phy.position.x)/5.f;
                    ai->vZ = (pc->currentGoal->Zcoord - etcx.phy.position.z)/5.f;
                    // std::cout << "PATROL RETURN GOAL: " << pc->currentGoal->id << std::endl;
                }

                return BTnodeStatus::fail;
            }
        }
    }

    private:
        float mediumThreshold { 6.f };
        StBeh stbeh;
        PathfollowingSys pfsys;
};