#pragma once
#include <ecs/util/globals.hpp>

namespace ECS
{
    struct EntityManager;
}

struct CameraComponent;


struct CameraSystem
{
    explicit CameraSystem() = default;

    // ni idea de donde pilla raylib para el Vector3 xd
    // void init(EntityManager &em);
    bool update(ECS::EntityManager &g);
    ECS::Vector3 normalize(ECS::Vector3 vec);
    ECS::Vector3 substract(ECS::Vector3 vec1, ECS::Vector3 vec2);
    ECS::Vector3 scale(ECS::Vector3 v, float scalar);
    float dotProduct(ECS::Vector3 vec1, ECS::Vector3 vec2);
    void cameraMovForward(CameraComponent &cam, float distance);
    void cameraRotateForward(CameraComponent &cam, float angle);
    void cameraRotateRigth(CameraComponent &cam, float angle);
    void cameraMovRigth(CameraComponent &cam, float distance);
    ECS::Vector3 crossProduct(ECS::Vector3 v1, ECS::Vector3 v2);
    ECS::Vector3 getCameraForward(CameraComponent &cam);
    ECS::Vector3 getCameraRight(CameraComponent &cam);
    ECS::Vector3 getCameraUp(CameraComponent &cam);
    void cameraGoUp(CameraComponent &cam, float distance);
    ECS::Vector3 add(ECS::Vector3 v1, ECS::Vector3 v2);
    ECS::Vector3 rotateByAxisAngle(ECS::Vector3 v, ECS::Vector3 axis, float angle);
    float getAngle(ECS::Vector3 v1, ECS::Vector3 v2);
    ECS::Vector3 negate(ECS::Vector3 v);
    void cameraZoom(CameraComponent &cam, float zoom);
    void cameraFovy(CameraComponent &cam, float fovy);
    float distanceVector(ECS::Vector3 v1, ECS::Vector3 v2);
    void cameraResetValues(CameraComponent &cam);

private:
};