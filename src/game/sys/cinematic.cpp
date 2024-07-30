#include <game/sys/cinematic.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
#include <game/man/event/eventManager.hpp>
// factories
#include <game/factories/gameobjectfactory.hpp>
// cmp
#include <game/cmp/cinematicComponent.hpp>
#include <game/cmp/cameraComponent.hpp>
#include <game/cmp/inputComponent.hpp>
// util
#include <ecs/util/globals.hpp>

void CinematicSystem::update(ECS::EntityManager &em)
{
    auto &eventM = em.getSingletonComponentEM<EventManager>();
    auto &cinematicC = em.getSingletonComponentEM<CinematicComponent>();
    auto *player = em.getPlayer();
    if(player) {
        auto *playerInput  = player->getComponent<InputComponent>();

        if (eventM.getEventType().ContainsLayer(EventMask::CINEMATIC))
        {
            cinematicC.mDeltaTime = std::chrono::system_clock::now() - cinematicC.mStartTime;
            if (cinematicC.mDeltaTime.count() >= cinematicC.cinematicTime)
            {
                // CameraComponent::currentCam = ECS::ID_INIT_CAM; // vuelvo a la camara del jugador
                CameraComponent::currentCam = cinematicC.idLastCam;
                eventM.getEventType().RemoveLayer(EventMask::CINEMATIC);

                if(playerInput)
                    playerInput->blockInput = false;
            }
        }
    }
}