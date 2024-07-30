#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <vector>
#include <cstdint>

struct BoundingBox_t
{
    float xMin{0}, yMin{0}, zMin{0};
    float xMax{0}, yMax{0}, zMax{0};
};

struct ColliderComponent : ECS::Component
{
    explicit ColliderComponent(std::size_t eID)
        : ECS::Component(eID){};

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(6);
    }

    enum{
        State_IDLE      = 0x00,
        State_Friction  = 0x01,
        State_Collision = 0x02
    };

// usar para despues, hacelro mas optimo
    enum {
        P_Nothing       = 0x00, 
        P_NOOVERLAP     = 0x01, // para el overlap
        P_IsPlayer      = 0x02,
        P_IsBox         = 0x04,
        P_IsFloorType1  = 0x08,
        P_IsIA          = 0x16        
    };

    uint8_t properties { P_Nothing };
    uint8_t mask { 0xFF };
    BoundingBox_t box;
    bool isActive { true }; // si no esta activo no chocará
    // bool collided{false};
};
