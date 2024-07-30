// raiz
#include <game/events/damageEvent.hpp>
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

void DamageEvent::handle(ECS::EntityManager &em, GraphicEngine &GE, AudioEngine &audio)
{
    for (auto &health : em.getComponents<HealthComponent>())
    {
        auto *e = em.getEntityByID(health.getEntityID());
        if (e)
        {
            if (health.damaged) {
                e->getComponent<RenderComponent>()->color = {1.0f,0.0f,0.0f};
            }
            else {
                e->getComponent<RenderComponent>()->color = e->getComponent<RenderComponent>()->damaged_color_reset;
            }
        }
    }
}