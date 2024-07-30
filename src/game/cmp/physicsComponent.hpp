#pragma once
// engines
#include <engines/physics/body/worldPhysics/physicsRules.hpp>
// cmp
#include <ecs/cmp/component.hpp>
// libs
#include <cstdint>
#include <numbers>
#include <algorithm>
#include <cmath>
// util
#include <game/util/LayerMask.hpp>
// openGL
#include <glm/glm.hpp>

#define PI 3.14159265358979323846f
// si me sobra tiempo, tengo que desacoplar esto, para que use una clase del motor de fisicas por separado

struct PhysicsComponent : ECS::Component
{
    explicit PhysicsComponent(std::size_t eID)
        : ECS::Component(eID){
          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(2);
    }

    // posicion, velocidad
        glm::vec3 position{0.f,0.f,0.f}; // posicion en el mundo del objeto
        glm::vec3 velocity{0.f,0.f,0.f}; // velocidad del objeto
        glm::vec3 aceleration{0.f,0.f,0.f}; // aceleracoin del objeto

        float mass{10}; // masa del objeto fisico
        float invMass{0.1f}; // masa inversa para calculo de impulsos
        glm::vec3 force{0.f,0.f,0.f}; // fuerza total del objeto
        glm::vec3 forceDirection{0.f,0.f,0.f}; // direccion de la fuerza del objeto
        glm::vec3 externForces{0.f,0.f,0.f}; // fuerzas externas aplicadas al objeto
        glm::vec3 ownForces{0.f,0.f,0.f}; // fuerza propia que ejerce el cuerpo
        float maxForceSprint{8000.f}; // maxima fuerza de velocidad permitida
        float staticFriction{0.6f}; // rozamiento estatico
        float dynamicFriction{0.4f}; // rozamiento dinamico
        float air_drag{0.75f}; // rozamiento en el aire
        float restitution{0.5f}; // coef. restitucion para impulsos
        float density{0}; // densidad el objeto

        glm::vec3 normal{0.f,0.f,0.f}; // normal del objeto 
        float depth{0.f}; // profuncidad para colisiones - no añadido

        glm::vec3 dimension{0.f,0.f,0.f}; // dimensiones del objeto
        bool isInGround{false}; // saber si esta en tierra o no
        bool hasImpulse{true}; // permitirle tener reacciones con objetos

    // propiedades fisicas
        bool use_gravity{true}; // uso de gravedad
        glm::vec3 gravityForce{0.f,-9.8f,0.f}; // fuerza de gravedad

    // tipo de comportamiento en el mundo
        bool dynamic_{false};
        bool static_{false};
        bool kinematic_{false};
        
        bool camare_{false};

        bool trigger{false};
        bool triggerCollision{false};

    // reglas para la fisica
        PhysicRules rules{};
        LayerMask layer{}; // layer al que pertenece el objeto fisico

    // ///////////////////////////////////////////////////////
    // DE AQUI PARA ABAJO SON VARIABLES PARA LA IA ---------------------------------
    float velAng { 0.0f };
    float orientation { 0.0f };

    float aLinear {};
    float aAng    {};

    static constexpr float velLinearMax { 1.75f };
    static constexpr float velAngMax { 3*PI };

    static constexpr float maxALin { 1.5f/* 0.07f */ };  //{ KMaxVxz/2.0f };
    static constexpr float maxAAng { velAngMax/2.0f };

};
