#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// libs
#include <vector>
#include <cstdint>

struct Entity;

struct DoorComponent : ECS::Component
{
    explicit DoorComponent(std::size_t eID)
        : ECS::Component(eID){};

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(9);
    }

    // bool isOpen{false};
    // tipo de llave para una puerta en especifico
    // ECS::DoorType keyType{ECS::DoorType::NONE_KEY};
    // // tipo de puerta que ira con una llave en especifico
    // ECS::EntityType doorType{ECS::EntityType::NONE}; // solo tendra el valor de las llaves
    // si la llave y la purta tienen el mismo tipo, da igual que puerta habras en que momento mientras sean del mismo tipo

    // bool puzle_completed { false };
    // ECS::Entity *key;
    ECS::EntityType doorType{ECS::EntityType::NONE};
    ECS::EntityTAG keyTag{ECS::EntityTAG::NO_TAG};
};