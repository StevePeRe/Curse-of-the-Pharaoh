#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// libs
#include <chrono>
#include <cstdint>

struct HealthSystem;
struct DamageEvent;

struct HealthComponent : ECS::Component
{

    explicit HealthComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(11);
    }

    bool damaged{ false };
    float health{100};
    float damage{25};
    // tiempo de inmunidad para no recibir daño
    bool hasInmunity{true};
    bool initInmunity{false};
    float inmunityTime{.5f};

    u_int32_t inminityHits{0};
    // bool onCoolDown { false };

private:
    friend HealthSystem; //puede usar mis funciones privadas
    friend DamageEvent;
    std::chrono::system_clock::time_point mStartTime{};
    std::chrono::duration<float> mDeltaTime{};
    
};