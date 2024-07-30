#include <game/sys/event.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// sonido
#include <engines/audio/AudioEngine.hpp>
// Graphic
#include <engines/graphic/GraphicEngine.hpp>
// libs
#include <chrono>
#include <iostream>

void EventSystem::updateTriggers()
{
    // AQUI NO HACER LO del timer, que haya un power up a parte
    for (auto &events : *eventManager)
    {
        events.get()->handle(EntityMan, GE, audioEngine);
    }
    eventManager->clearAllEvents();
}

void EventSystem::lateUpdate()
{
    // todos los triggers generales
    // /////////////////////////////////////////////////////////////////////////////
    // se pone y se elimina todo el rato que colisione con el trigger, TODO optimizarlo
    if (eventManager->getEventType().ContainsLayer<EventMask>(EventMask::EXTERIOR_MUSIC))
    {
        if ((eventTag & ECS::EventTAG::NO_PLAYING) || !(eventTag & ECS::EventTAG::EXT_PLAYING))
        {
            /* std::cout << "cambio a menu music\n"; */
            audioEngine.stopAll();
            audioEngine.createInstance("Menu Music", "Musica/desert music")->Play();
            eventTag = ECS::EventTAG::EXT_PLAYING;
        }
        eventManager->getEventType().RemoveLayer<EventMask>(EventMask::EXTERIOR_MUSIC); // quito el tipo una vez ejecutado
    } 
    // /////////////////////////////////////////////////////////////////////////////
    if (eventManager->getEventType().ContainsLayer(EventMask::COMBAT_MUSIC))
    {
        if ((eventTag & ECS::EventTAG::NO_PLAYING) || !(eventTag & ECS::EventTAG::COMB_PLAYING))
        {
            audioEngine.stopAll();
            auto *music_level = audioEngine.createInstance("Dungeon Music", "Musica/dark");
            music_level->Play();
            music_level->SetVolume(0.25f);
            eventTag = ECS::EventTAG::COMB_PLAYING;
        }
        eventManager->getEventType().RemoveLayer(EventMask::COMBAT_MUSIC);
    } 
    // /////////////////////////////////////////////////////////////////////////////
    if (eventManager->getEventType().ContainsLayer(EventMask::DUNGEON_MUSIC))
    {
        if ((eventTag & ECS::EventTAG::NO_PLAYING) || !(eventTag & ECS::EventTAG::DUNG_PLAYING))
        {
            /* std::cout << "cambio a dungeon music\n"; */
            audioEngine.stopAll();
            auto *music_level = audioEngine.createInstance("Dungeon Music", "Musica/dark");
            music_level->Play();
            music_level->SetVolume(0.25f);
            eventTag = ECS::EventTAG::DUNG_PLAYING;
        }
        eventManager->getEventType().RemoveLayer(EventMask::DUNGEON_MUSIC);
    } 
    // /////////////////////////////////////////////////////////////////////////////
    if (eventManager->getEventType().ContainsLayer(EventMask::POWER_UP_MUSIC))
    {
        audioEngine.createInstance("PowerUp", "Efectos/power_up")->Play();
        eventManager->getEventType().RemoveLayer(EventMask::POWER_UP_MUSIC);
    }
    // /////////////////////////////////////////////////////////////////////////////
    if (eventManager->getEventType().ContainsLayer(EventMask::PICK_OBJECT))
    {
        audioEngine.createInstance("Pick Object", "Efectos/save_game")->Play();
        eventManager->getEventType().RemoveLayer(EventMask::PICK_OBJECT);
    }
    // /////////////////////////////////////////////////////////////////////////////
    if (eventManager->getEventType().ContainsLayer(EventMask::PZ_COMPLETED))
    {
        audioEngine.createInstance("COMPLETED_PUZLE", "Ambiente/safe_room")->Play();
        /* audioEngine.getInstances("COMPLETED_PUZLE")[0]->SetVolume(1.f); */
        eventManager->getEventType().RemoveLayer(EventMask::PZ_COMPLETED);
    }
}