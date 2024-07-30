#pragma once
// trigger
#include <game/man/event/eventTrigger.hpp>
// libs
#include <chrono>

namespace ECS{
    struct EntityManager;
}

struct DamageEvent : eventTrigger
{
    using startTime = std::chrono::system_clock::time_point;
    using durationDT = std::chrono::duration<float>;
    // explicit DamageEvent() = default;
    explicit DamageEvent(bool dur, float time) : hasDuration{dur}, durationTime{time}
    {
        
    };
    void handle(ECS::EntityManager &em, GraphicEngine &GE, AudioEngine &audio) override;

    private:
    bool hasDuration{false};
    float durationTime{1.f};
    startTime mStartTime{};
    durationDT mDeltaTime{};
    bool initCount{true}; // siempre true primero para entrar la primera vez
};