#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// libs
#include <cstdint>

struct InputComponent : ECS::Component
{

    explicit InputComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(8);
    }

    int lastOrientation{87}; // hacia delante
    bool interaction{false};
    bool useAMMO{false};
    bool message_erase{false};
    bool useInventory{false};
    bool blockInput{false};
    private:
    
};
