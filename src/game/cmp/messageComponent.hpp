#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// utils
#include <ecs/util/globals.hpp>
// libs
#include <string>
#include <cstdint>

struct MessageComponent : ECS::Component
{

    explicit MessageComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(17);
    }

    // diferenciar mensajes solo para leer una vez para saber como se usan las cosas/activan
    // leer todo un dialogo
    const char* message{};
    const char* messageUse = "PULSA E";
    bool showMessage{false};
    bool justUsePopUpE{false}; // solo dejar que lo use los objetos interactuabls
    bool justUseMessages{false};
    // saber como se usan, si con la E, etc

};