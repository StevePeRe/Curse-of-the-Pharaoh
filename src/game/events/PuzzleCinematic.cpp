// raiz
#include <game/events/PuzzleCinematic.hpp>
// manager
#include <ecs/man/entitymanager.hpp>
#include <game/man/event/eventManager.hpp>
// audio
#include <engines/audio/AudioEngine.hpp>
// Graphic
#include <engines/graphic/GraphicEngine.hpp>
// cmp
#include <game/cmp/cameraComponent.hpp>
#include <game/cmp/cinematicComponent.hpp>
// libs
#include <chrono>
#include <iostream>

void CinematicEvent::handle(ECS::EntityManager &em, GraphicEngine &GE, AudioEngine &audio)
{
    auto &cinematicC = em.getSingletonComponentEM<CinematicComponent>();
    auto &eventM     = em.getSingletonComponentEM<EventManager>();
    auto *player     = em.getPlayer();

    CameraComponent::currentCam = ECS::ID_MOVABLE_CAM; // cambio a la camara de cinematica
    auto *entCam = em.getEntityByTAG(ECS::EntityTAG::MOVIBLE_CAM);

    if(entCam){
        auto *cam = entCam->getComponent<CameraComponent>();
        if(cam){
            std::cout << "entro cinematic\n";
            cam->cameraPosition.x = -40.619f;
            cam->cameraPosition.y = 12.9591f;
            cam->cameraPosition.z = -84.8967f;

            cam->cameraTarget.x = -53.1613f;
            cam->cameraTarget.y = -0.88757f;
            cam->cameraTarget.z = -111.017f;

            cam->cameraUp.x = 0.f;
            cam->cameraUp.y = 0.998f;
            cam->cameraUp.z = 0.f;
        }
    }

    eventM.addEventType(EventMask::CINEMATIC); // para avisarle al sys cinematic que lance la cinematica

    cinematicC.mStartTime = std::chrono::system_clock::now();
    cinematicC.cinematicTime = 4.f;
}