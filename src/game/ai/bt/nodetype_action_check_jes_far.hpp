#pragma once
#include "node.hpp"
#include <game/ai/bb/blackboardComponent.hpp>
#include <game/ai/sb/stbeh.hpp>
// cmp
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/audioComponent.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// lib
#include <iostream>
#include <ecs/util/globals.hpp>

struct BTactionCheckJesFar : BTnode
{
    BTactionCheckJesFar() {}

    BTnodeStatus run(EntityContext &etcx, float dt) noexcept final
    {
        // std::cout<< "entro en check jes far" << std::endl;

        auto ai = etcx.ent.getComponent<AIComponent>();

        BlackBoardComponent &bb = etcx.entman.getSingletonComponentEM<BlackBoardComponent>(); // para escarabajos

        if ((ai->enemyType != 2 && stbeh.perception(*ai, dt))) // revisar perception, tendria que ir al target encontrado y no buscar otra target hasta que no pase el tiempo dt
        // a lo mejor puede ser porque le aplico una fuerza y la friccion quita esa fuerza que le pongo, y como no le vuelvo a poner fuerza se queda quieto hasta que ve al player de nuevo
        {
            bool tf;
            tf = check(*ai, etcx);
            if (tf)
            {
                // std::cout<< "I CAN PERCEIVE YOU" << std::endl;
                // std::cout << "jes is FAR" << std::endl;
                return BTnodeStatus::success;
            }
            else
            {
                // std::cout<< "I CANNOT PERCEIVE YOU" << std::endl;
                return BTnodeStatus::fail;
            }
        }
        else if (ai->enemyType == 2 && stbeh.perceptionBB(bb, *ai, dt))
        { // escarabajos
            if (bb.tactive)
            {
                ECS::Entity *player = etcx.entman.getPlayer();
                const auto &playerPhy = player->getComponent<PhysicsComponent>();
                bb.tx = playerPhy->position.x;
                bb.tz = playerPhy->position.z;
                return BTnodeStatus::success;
            }
            else
            {
                bool tf;
                tf = check(*ai, etcx);
                if (tf)
                {
                    bb.tx = ai->tx;
                    bb.tz = ai->tz;
                    // bb.behaviour = SB::Seek;
                    bb.tactive = ai->tactive;
                    return BTnodeStatus::success;
                }
                else
                {
                    return BTnodeStatus::fail;
                }
            }
        }
        return BTnodeStatus::fail;
    }

    // para que siga a Jess
    // separa el check por Percepcion
    bool check(AIComponent &ai, EntityContext &etcx)
    {
        bool check = false;
        ECS::Entity *player = etcx.entman.getPlayer();
        auto *playerPhy = player->getComponent<PhysicsComponent>();
        // visual
        auto *percIA = etcx.ent.getComponent<PerceptionComponent>();

        if (percIA && playerPhy)
        {
            if (percIA->seen || percIA->heard)
            {
                std::cout << "entro en IA lo veo check far BBBBBBBBBBBB\n";
                ai.tactive = true;
                ai.tx = playerPhy->position.x;
                ai.tz = playerPhy->position.z;
                check = true;
            }
        }

        return check;
    }

private:
    StBeh stbeh;
};