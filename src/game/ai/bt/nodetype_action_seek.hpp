#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
#include <game/cmp/aiComponent.hpp>
#include <ecs/cmp/entity.hpp>
#include <ecs/man/entitymanager.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <engines/physics/body/bodyComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/animationComponent.hpp>
#include <ecs/util/globals.hpp>
#include <iostream>
#include <game/ai/sb/stbeh.hpp>

struct BTactionSeek : BTnode{
    BTactionSeek() {}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{

        auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 10;
       
        Steer st = stbeh.seek(*ai, etcx.phy, *etcx.ent.getComponent<AnimationComponent>());
        ai->vX = st.linearVX;
        ai->vZ = st.linearVZ;
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