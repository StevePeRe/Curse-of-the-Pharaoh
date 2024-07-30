#pragma once
#include <game/man/event/eventManager.hpp>
// json
#include <game/util/GameDataManager.hpp>

namespace ECS{
    struct EntityManager;
}

struct GraphicEngine;
struct AudioEngine;

struct EventSystem
{
    explicit EventSystem(EventManager &event, ECS::EntityManager &em, AudioEngine &ae, GraphicEngine &ge) : eventManager(&event),  
        EntityMan{em}, audioEngine{ae}, GE{ge}{}
    void updateTriggers();

    void lateUpdate();

private:
    EventManager *eventManager{nullptr};
    ECS::EntityManager &EntityMan;
    AudioEngine &audioEngine;
    GraphicEngine &GE;
    GameDataManager manageData;

    // flags para las musicas del nivel
    ECS::EventTAG eventTag{ECS::EventTAG::NO_PLAYING};
};