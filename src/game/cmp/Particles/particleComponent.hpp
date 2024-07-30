#pragma once
// cmp
#include <ecs/cmp/component.hpp>
#include <game/cmp/Particles/particleType/particle.hpp>
// utils
#include <ecs/util/globals.hpp>
// libs
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
// openGL
#include <glm/glm.hpp>

struct ParticleComponent : ECS::Component
{

    explicit ParticleComponent(std::size_t eID)
        : ECS::Component(eID){
                // reservo para cada entidad un vector de 10, para que tenga de maximo 10 particulas cada una
            // particle.reserve(10); // max 10 particulas
          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(22);
    }

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 color;
    float size;
    float life; // Tiempo de vida restante de la partícula

    // std::vector<std::unique_ptr<Particle>> particle;
    // vector de particles, de lava, tierra, etc -> hijos de particle.hpp 
    // creo el particleSys, aqui llamo a su handle de cada clase particle -> particleTierra o particleLava, como en el puzzle vaya
    // si existe en el vector particulas y estan activas, las creo con otra clase que sera ParticleGenerator
    // con esto pillo la clase que contiene el vector "particleTierra" por ejemplo, y le digo que me genere una cantidad
    // de particulas con posicion random, vel random etc, que todo eso random estara en el ParticleGenerator.
    // Generara las particulas de tierra, y luego vera si hay mas particuals activas, si si, hace lo mismo
    // y en el Sys supongo que se llamaria cada vez al motor grafico para que las pinte

};