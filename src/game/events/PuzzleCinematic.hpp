#pragma once
// trigger
#include <game/man/event/eventTrigger.hpp>
// libs
#include <chrono>

namespace ECS{
    struct EntityManager;
}

struct CinematicEvent : eventTrigger
{
    // explicit DamageEvent() = default;
    explicit CinematicEvent() 
    {
        // pasarle los parametros que quiero que tenga para modificar la camara
        // creo que solo necesito el eM
        // seria incluir el camaracoponent, cambairla, aplicar los valores necesarios y lanzar los eventos
        // cambiarle los valores al cinematic component del tiempo para que se haga en su Sys las ejecuciones que hagan falta
    };
    void handle(ECS::EntityManager &em, GraphicEngine &GE, AudioEngine &audio) override;

    private:

};