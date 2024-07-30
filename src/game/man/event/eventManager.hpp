#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// triggers
#include <game/man/event/eventTrigger.hpp>
// #include <game/man/event/messageTrigger.hpp>s
// util
#include <game/util/LayerMask.hpp>
#include <ecs/util/globals.hpp>
// libs
#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>

struct EventManager : ECS::SingletonComponent
{
    explicit EventManager() : ECS::SingletonComponent(ECS::IDSingleCMPEventM) 
    { 
        triggers_.reserve(50); 
    }

    template <typename EventType>
    void newTriggerEvent(EventType event) noexcept {
        triggers_.emplace_back( std::make_unique<EventType>(event) );
    }

    [[nodiscard]] auto begin() noexcept { return triggers_.begin(); }
    [[nodiscard]] auto end()   noexcept { return triggers_.end(); }

    std::vector<std::unique_ptr<eventTrigger>> &getTriggerVector() noexcept { return triggers_;}

    void clearAllEvents() noexcept
    {
        triggers_.clear();
    }

    // Eventos generales del juego
    template<typename MASK>
    void addEventType(MASK type){ 
        if(!(eventType.ContainsLayer(type)))
            eventType.AddLayer(type); 
    }
    LayerMask &getEventType() { return eventType; }

    static std::size_t getSingletonComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(ECS::IDSingleCMPEventM);
    }

private:
    std::vector<std::unique_ptr<eventTrigger>> triggers_{};
    LayerMask eventType{};
};
