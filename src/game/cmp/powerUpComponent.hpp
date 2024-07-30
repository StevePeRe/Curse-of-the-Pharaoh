#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// utils
#include <ecs/util/globals.hpp>
#include <game/util/LayerMask.hpp>
// libs
#include <string>
#include <cstdint>

struct PowerUpComponent : ECS::Component
{

    explicit PowerUpComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(23);
    }

    // SHOTGUN MODE
    float shots{3};
    
    // INMUNITY MODE
    u_int32_t inminityHits{3};

    // ENEMIGOS ESTATICOS
    float freezeTime{5.f};

    LayerMask layer{}; // powerUps activos a la vez

};
