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

struct BTactionArrive : BTnode{
    BTactionArrive() {}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{

        auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 1;
       
        Steer st = stbeh.arrive(*ai, etcx.phy);
        ai->vX = st.linearVX*30;
        ai->vZ = st.linearVZ*30;
        if(ai->enemyType == 2){
            st.linearVX = ai->vX;
            st.linearVZ = ai->vZ;
            stbeh.flock(*ai, etcx.phy, st, etcx.entman);
            ai->vX = st.linearVX;
            ai->vZ = st.linearVZ;
        }
  
        return BTnodeStatus::success; 
    }

    private:
        StBeh stbeh;
};