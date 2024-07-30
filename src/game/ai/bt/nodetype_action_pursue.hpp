#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
#include <iostream>
#include <game/ai/sb/stbeh.hpp>
#include <game/ai/pf/pathFollowingSys.hpp>
#include <game/ai/pf/pathComponent.hpp>
// cmp
#include <game/cmp/audioComponent.hpp>
// Graphic Engine
#include <engines/graphic/GraphicEngine.hpp>
// lib
#include <glm/glm.hpp>
#include <cmath>

struct BTactionPursue : BTnode{
    BTactionPursue() = default;

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        // std::cout<< " action pursue" << std::endl;
        auto *audio  = etcx.ent.getComponent<AudioComponent>();

        auto *ai = etcx.ent.getComponent<AIComponent>();
        [[maybe_unused]]float deltaT = dt;

        // std::cout << "rendia pasado " << ai->behaviour << std::endl;

        Steer st;
        switch(ai->behaviour){
            case SB::Arrive:
                // std::cout << "arrives: " << std::endl;
                st = stbeh.arrive(*ai, etcx.phy);
                ai->vX = st.linearVX;
                ai->vZ = st.linearVZ;
            break;
            case SB::Seek:
                // std::cout << "seek: " << std::endl;
                st = stbeh.seek(*ai, etcx.phy, *etcx.ent.getComponent<AnimationComponent>());
                ai->vX = st.linearVX;
                ai->vZ = st.linearVZ;
            break;
            case SB::Flee:
                st = stbeh.flee(*ai, etcx.phy);
            break;
            case SB::Pathfollowing:
                auto pc = etcx.ent.getComponent<PathComponent>();
                pfsys.update(etcx.entman, *pc, etcx.phy, ECS::currentlevel);
            break;
        }

        if(ai->vX != 0 || ai->vZ != 0) // no divir entre 0
            etcx.phy.forceDirection = glm::normalize(glm::vec3{st.linearVX, 0.f, st.linearVZ});
        
        if(ai->enemyType == 2){
            // st = stbeh.evade(*ai, etcx.phy, st, etcx.entman);
            st = stbeh.flock(*ai, etcx.phy, st, etcx.entman);
        }
        /* st.linearVX *= 200;
        st.linearVZ *= 200; */
        

        /* std::cout << "force: " << etcx.phy.forceDirection.x << " , " << etcx.phy.forceDirection.z << "\n"; */
        etcx.phy.ownForces.x += st.linearVX*650.f; // si eso ponerle mas max Velocity a la IA
        etcx.phy.ownForces.z += st.linearVZ*650.f;
        // std::cout << "velocidIA: " << st.linearVX << " , " << st.linearVZ << "\n";
        // std::cout << "force: " << etcx.phy.ownForces.x << " , " << etcx.phy.ownForces.z << "\n";
        //etcx.phy.orientation = st.angularV;

        // if(audio && !(audio->getAudioInstance("AGRO_ZOMBIE")->GetState() == AudioInstance::AudioState::PLAYING)){
        //     audio->play("AGRO_ZOMBIE");
        // } 
        /* ray->direction      = IAForward; */

        // return BTnodeStatus::running;
        return BTnodeStatus::success;
    }

    private:
        StBeh stbeh;
        PathfollowingSys pfsys;
};