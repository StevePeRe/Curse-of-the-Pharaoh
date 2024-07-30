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

struct BTactionFlee : BTnode{
    BTactionFlee() {}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        // std::cout << "entro en flee" << std::endl;

        auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 6;
       
        Steer st = stbeh.flee(*ai, etcx.phy);
        ai->vX = st.linearVX*30;
        ai->vZ = st.linearVZ*30;
  
        return BTnodeStatus::success; 
    }

    private:
        StBeh stbeh;
};