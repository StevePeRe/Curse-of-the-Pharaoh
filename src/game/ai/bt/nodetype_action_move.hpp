#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
// cmp
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/healthComponent.hpp>
#include <game/ai/pf/pathFollowingSys.hpp>
// lib
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

struct BTactionMove : BTnode{
    BTactionMove(){}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        // std::cout<< "move" << std::endl;
        auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 9;

        if (ai->enemyType != 2)
        {
            auto anim_ = etcx.ent.getComponent<AnimationComponent>();
            if (anim_->anim != nullptr)
                if (anim_->anim->checkEndAnimation() || anim_->anim->getCurrentAnimation() != anim_->walk)
                    anim_->anim->setAnimation(anim_->walk);
        }
        // else{
        //     Steer st;
        //     st.linearVX = ai->vX;
        //     st.linearVZ = ai->vZ;
        //     stbeh.flock(*ai, etcx.phy, st, etcx.entman);
        //     ai->vX = st.linearVX;
        //     ai->vZ = st.linearVZ;
        // }

        etcx.phy.ownForces.x = ai->vX*1000;
        etcx.phy.ownForces.z = ai->vZ*1000;  
        // std::cout << "ownforces: " << etcx.phy.ownForces.x << ", " << etcx.phy.ownForces.z << std::endl; 

        return BTnodeStatus::success;
    }

    private:
    StBeh stbeh;
};