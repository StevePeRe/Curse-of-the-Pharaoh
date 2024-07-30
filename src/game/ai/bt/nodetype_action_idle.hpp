#pragma once
#include "node.hpp"
#include <iostream>
#include <game/ai/sb/stbeh.hpp>
#include <game/cmp/animationComponent.hpp>

struct BTactionIdle : BTnode
{
    BTactionIdle() {}

    BTnodeStatus run(EntityContext &etcx, float dt) noexcept final
    {
        // std::cout<< "idle" << std::endl;
        auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 8;
        [[maybe_unused]] float deltaT = dt;

        if (ai->enemyType != 2)
        {
            auto anim_ = etcx.ent.getComponent<AnimationComponent>();
            if (anim_->anim != nullptr)
                if (anim_->anim->checkEndAnimation() || anim_->anim->getCurrentAnimation() != anim_->idle)
                    anim_->anim->setAnimation(anim_->idle);
        }

        // if(!ai->tactive){
        auto st = stbeh.idle(*ai, etcx.phy, *etcx.ent.getComponent<AnimationComponent>());

        ai->vX = st.linearVX * 10;
        ai->vZ = st.linearVZ * 10;

        return BTnodeStatus::success;
        // }
    }

private:
    StBeh stbeh;
};