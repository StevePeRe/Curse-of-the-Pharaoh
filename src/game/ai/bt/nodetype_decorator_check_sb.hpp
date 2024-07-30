#pragma once
#include "node.hpp"
#include <iostream>
#include <glm/glm.hpp>

struct BTdecoratorCheckSB : BTnode {
    BTnode* ch_arrive;
    BTnode* ch_seek;
    BTnode* ch_flee;
    BTnode* ch_pathfollowing;

    BTdecoratorCheckSB(BTnode* ch_arrive, BTnode* ch_seek, BTnode* ch_flee, BTnode* ch_pathfollowing): ch_arrive(ch_arrive), ch_seek(ch_seek), ch_flee(ch_flee), ch_pathfollowing(ch_pathfollowing){
    }

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final {
        auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 12;

        switch(ai->behaviour){
            case SB::Arrive:
                return ch_arrive->run(etcx, dt);
            break;
            case SB::Seek:
                return ch_seek->run(etcx, dt);
            break;
            case SB::Flee:
                return ch_flee->run(etcx, dt);
            break;
            case SB::Pathfollowing:
                return ch_pathfollowing->run(etcx, dt);
            break;
            default: //ERROR
                return BTnodeStatus::fail;
            break;
        }
    }

    private:
};
