#include <game/sys/spawn.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/spawnerComponent.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <iostream>

void SpawnSystem::update(ECS::EntityManager &em)
{
    using namespace std::chrono;
    auto now = steady_clock::now();
    for(auto& spawn : em.getComponents<SpawnerComponent>()) {
        auto passed { now - spawn.last_spawn_time };
        auto *e = em.getEntityByID(spawn.getEntityID());
        if(e && spawn.to_be_spawned > 0 && passed > spawn.spawn_interval){
            std::cout << "Crear objeto\n";
            spawn.spawnMethod(spawn);

            spawn.last_spawn_time = now; // reset de contador
            --spawn.to_be_spawned; // cantidad de veces que se spawnea
        }
    }
}