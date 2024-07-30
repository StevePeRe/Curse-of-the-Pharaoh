#pragma once
#include <ecs/util/globals.hpp>


namespace ECS
{
    struct Entity;
    struct EntityManager;
}

struct ElevatorSystem
{
    explicit ElevatorSystem() = default;

    void update(ECS::EntityManager &em);
    void checkCollision(ECS::Entity &player, ECS::Entity &cmp);

    private:
    bool isActive{false}; // si esta activo o no
    // bool moveBlocked{false}; // movimiento bloqueado del ascensor
    float high{0}, low{0}; // altura min y max a la que llega
    float l_high{0}, l_low{0}; // altura min y max a la que llega
    float r_high{0}, r_low{0}; // altura min y max a la que llega

    ECS::SwitchType switchType{ECS::SwitchType::NONE_ELEVATOR}; // auxiliar para decirle que switch ha sido activado
};