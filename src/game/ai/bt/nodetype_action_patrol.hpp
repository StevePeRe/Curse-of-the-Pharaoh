#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
// cmp
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/healthComponent.hpp>
#include <game/ai/pf/pathFollowingSys.hpp>
/* #include <game/cmp/physicsComponent.hpp> */
// Graphic Engine
// #include <engines/graphic/GraphicEngine.hpp>
// lib
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

struct BTactionPatrol : BTnode{
    BTactionPatrol(){}

    BTnodeStatus run(EntityContext& etcx, [[maybe_unused]]float dt) noexcept final{
        // std::cout<< "patrol" << std::endl;
        auto pc = etcx.ent.getComponent<PathComponent>();
        Steer st;

        if(!pc->patrolInitialized){
            // pfsys.setPatrolMomia(*pc, etcx.phy);
            // std::cout<< "patrol has been set" << std::endl;
        }

        // st = pfsys.patrolEnemy(*pc, etcx.phy);

        // std::cout << "st recibido: " << st.linearVX << ", " << st.linearVZ << std::endl;

        etcx.phy.ownForces.x = st.linearVX*1000;
        etcx.phy.ownForces.z = st.linearVZ*1000;   
        
        // std::cout << "ownforces: " << etcx.phy.ownForces.x << ", " << etcx.phy.ownForces.z << std::endl;

        return BTnodeStatus::success;
    }

    private:
        PathfollowingSys pfsys;
};