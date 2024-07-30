#pragma once
// cmp
#include <ecs/cmp/component.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
// utils
#include <ecs/util/globals.hpp>
// libs
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

struct ArrowTrapComponent : ECS::Component
{

    explicit ArrowTrapComponent(std::size_t eID)
        : ECS::Component(eID){
            shots.reserve(5);
          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(24);
    }

    // std::vector<std::unique_ptr<ShotBehaviourComponent>> shots;
    bool trapActive{false};

    // direccion de la trampa
};