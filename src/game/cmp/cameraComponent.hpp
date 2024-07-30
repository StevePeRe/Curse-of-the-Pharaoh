#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <vector>
#include <cstdint>

struct CameraComponent : ECS::Component
{

    explicit CameraComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(4);
    }

    void changeCurrentCam()
    {
        currentCam = idCam;
        currentOrientation = orientation;
    }

    int idCam{1};
    inline static int currentCam{1};
    inline static int lastCam{999};
    inline static int currentOrientation{ECS::ORIENTATION::NORTH};
    ECS::Vector3 cameraPosition{ECS::CAMERA_CUADRANTE_ESQUINA_AMARILLO_VERDE};
    ECS::Vector3 cameraTarget{ECS::CAMERA_TARGET__ESQUINA_AMARILLO_VERDE};
    ECS::Vector3 cameraUp{ECS::CAMERA_UP};
    float cameraFovy{ECS::CAMERA_FOVY};
    int orientation{ECS::ORIENTATION::NORTH};
    // int angulo {ECS::ANGULOS::ANGULO_AMARILLO_VERDE};
};