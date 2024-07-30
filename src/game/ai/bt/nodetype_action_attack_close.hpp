#pragma once
#include "node.hpp"
#include <ecs/util/globals.hpp>
// cmp
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/animationComponent.hpp>
/* #include <game/cmp/physicsComponent.hpp> */
// Graphic Engine
#include <engines/graphic/GraphicEngine.hpp>
// lib
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

struct BTactionAttackClose : BTnode{
    BTactionAttackClose(){}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        // std::cout<< "attack close" << std::endl;
        ECS::Entity* player = etcx.entman.getPlayer();
        /* if(!player){
            return;
        } */
        const auto &playerPhy = player->getComponent<PhysicsComponent>();

        [[maybe_unused]]auto ai = etcx.ent.getComponent<AIComponent>();
        ai->currentNode = 2;
        [[maybe_unused]]float deltaT = dt;

        /* auto ent1 = etcx.entman.getPlayer(); */
        auto *heath1 = player->getComponent<HealthComponent>();
        auto current_time = std::chrono::steady_clock::now();

        if (heath1 && !heath1->damaged)
        {
            if((current_time - last_attack) >= attack_wait)
            {
                heath1->damaged = heath1->initInmunity = true;
                heath1->damage = ai->damage;

                last_attack = current_time;
                /* std::cout<< "ME QUITA VIDA" << std::endl; */
            } 
            //subir para q haga mas daño?
            //en el futuro cambiarlo para que cada tipo de enemigo haga un daño distinto/poner contadores
        }

        return BTnodeStatus::success;
    }

    private:
        std::chrono::steady_clock::time_point last_attack;
        const std::chrono::milliseconds attack_wait{1500};
};