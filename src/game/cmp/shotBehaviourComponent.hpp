#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <glm/glm.hpp>
#include <chrono>
#include <cstdint>

struct ShotBehaviourComponent : ECS::Component
{

    // desde componentStorage create%%Component va metiendo e inicializando en el vector
    explicit ShotBehaviourComponent(std::size_t eID) : ECS::Component(eID){};

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(5);
    }

    // la tendran todas las entidades para que en un futuro puedan disparar ellas tmb
    // propiedades del disparo
    // bool start_shot{false};
    int16_t shot_maxAmmo{8};
    int16_t shot_ammo{0};
    int16_t shot_damage{0};
    glm::vec3 pos_inicial{-100.f};
    glm::vec3 direction{0.f};
    glm::vec3 velocity{0.f};
    // bool initRecharge{false};
    // float rechargeTime{1.5f};
    // contador, distanci que recorre hasta destruirse
    uint32_t initial_count{0};
    uint32_t counter{0};
    // contador, recarga
    std::chrono::milliseconds shoot_cooldown{1000}; // Intervalo de espera en milisegundos
    // std::chrono::system_clock::time_point mStartTime{};
    // std::chrono::duration<float> mDeltaTime{};
    // comportamiento base
    ECS::BehaviourState state{ECS::BehaviourState::IDLEB_S};
    ECS::BehaviourType type{ECS::BehaviourType::IDLEB};
    bool powerUpActive{false};

};
