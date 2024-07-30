#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// PE
#include <engines/physics/body/worldPhysics/raycastResult.hpp>
#include <engines/physics/body/worldPhysics/raycast.hpp>
// utils
#include <ecs/util/globals.hpp>
#include <game/util/LayerMask.hpp>
// libs
#include <string>
#include <cstdint>
#include <iostream>
#include <glm/glm.hpp>
#include <unordered_map>


namespace ECS
{
    struct Entity;
}

struct PerceptionComponent : ECS::Component
{
    using mapDetection = std::unordered_map<std::string, uint16_t>;

    explicit PerceptionComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(21);
    }

    // AUDIO PERCEPTION
    PerceptionComponent &addRadioSound(const char *soundTag, uint16_t distance = 2)
    {
        auto itr = radioSound.find(soundTag);
        if (itr == radioSound.end())
            radioSound.emplace(soundTag, distance);
        else
            std::cout << "\n**** ERROR al añadir sonido para detectar" << std::endl;

        return *this;
    }

    mapDetection &getMapDetection() { return radioSound; }

        // SIGTH PERCEPTION - RAYCAST
    bool hasSigth{false};
    bool useRaycast{true}; // usar el raycast
    LayerMask layersToDetect{}; // layer que quiere ver la entidad que tenga perception   
    Raycast raycast{}; // alamceno que colisiona
    bool seen{false}; // la entidad ha visto

        // AUDIO PERCEPTION
    bool hasHearing{false};
    mapDetection radioSound{}; // es para los que emiten sonidos
    bool heard{false}; // la entidad ha escuchado

};