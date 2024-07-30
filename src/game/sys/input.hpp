#pragma once
//#include <raylib.h>
#include <chrono>
#include <glm/glm.hpp>
// util
#include <game/util/GameDataManager.hpp>
#include <ecs/util/globals.hpp>

namespace ECS
{
    struct Entity;
    struct EntityManager;
}

struct PhysicsComponent;
struct GraphicEngine;
struct AnimationComponent;
struct AudioComponent;

struct InputSystem
{
    explicit InputSystem() = default;

    void update(ECS::EntityManager &em, GraphicEngine &ge);
    // void checkOrientation(PhysicsComponent &phy, ECS::Entity &e, GraphicEngine &ge);
    void OrientationPlayer(ECS::Entity &e, GraphicEngine &ge);
    // int getLastOrientation() { return lastOrientation; };
    void goToCheckpoint(PhysicsComponent& phy);
    inline static int lastOrientation{1};

    void checkAnimation(ECS::Entity &e, AnimationComponent *anim, AudioComponent &audio);

    glm::vec3 position;

private:
    // tiempo de espera disparo
    std::chrono::steady_clock::time_point last_shot_time;
    bool aim{false};
    bool player_bend{true};
    int lastRegisterKey{0};
    glm::vec3 lastTarget{0.f};
    glm::vec3 lastDirection{0.f};
    float maxForceSprint{0.f};
    GameDataManager manageData;
    glm::vec3 cameraForward;
    glm::vec3 cameraRigth;
    // const std::chrono::milliseconds shoot_cooldown{1000}; // Intervalo de espera en milisegundos
    // int16_t index{0}; // indice dle inventario
};