#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
////#include <raylib.h>
#include <cstdint>

struct SwitchComponent : ECS::Component
{

    explicit SwitchComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(20);
    }

    ECS::SwitchType switchType{ECS::SwitchType::NONE_ELEVATOR};
    // bool switched{false};
    // bool direction{false}; // false Down - true Up
    bool active{false}; // cuando colisiono con la entidad
};