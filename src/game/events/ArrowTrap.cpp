// raiz
#include <game/events/ArrowTrap.hpp>
// manager
#include <ecs/man/entitymanager.hpp>
// audio
#include <engines/audio/AudioEngine.hpp>
// Graphic
#include <engines/graphic/GraphicEngine.hpp>
// cmp
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/renderComponent.hpp>
// libs
#include <iostream>

void ArrowTrapEvent::handle(ECS::EntityManager &em, GraphicEngine &GE, AudioEngine &audio)
{
    // creo una flecha en una pos random en cada ejecucion
    // que haga la animacion de la placa
    
}