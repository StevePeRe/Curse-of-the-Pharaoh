#pragma once
// cmp
#include <ecs/cmp/component.hpp>
//util
#include <ecs/util/globals.hpp>
// libs
#include <cstdint>
#include <chrono>

struct ShotBehaviourComponent;
struct GraphicEngine;

struct CinematicComponent : ECS::SingletonComponent
{

    explicit CinematicComponent() : 
        ECS::SingletonComponent(ECS::IDSingleCMPCINEMATIC) {}

    static std::size_t getSingletonComponentTypeID() noexcept 
    { 
        return static_cast<std::size_t>(ECS::IDSingleCMPCINEMATIC); 
    }

    std::chrono::system_clock::time_point mStartTime{};
    std::chrono::duration<float> mDeltaTime{};
    float cinematicTime{4.f};
    std::size_t idLastCam{999};
};

