#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// utils
#include <ecs/util/globals.hpp>
// libs
#include <string>
#include <cstdint>

struct ElevatorComponent : ECS::Component
{

    explicit ElevatorComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(18);
    }

    bool active{false}; // cuando colisiono con la entidad
    bool working{false}; // cuando esta en proceso de subir o bajar, true para Up false para Down
    float distance_toDo{0.f};
    bool moveBlocked{false};
    float initial_position{0.f};
    float end_position{0.f};
    ECS::ElevatorDirection direction{ECS::ElevatorDirection::DIR_Y};

};