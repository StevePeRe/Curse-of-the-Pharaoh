#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <cstdint>
#include <array>
#include <chrono>
#include <functional>
//#include <game/ai/bt/behaviourtree.hpp>

// literals
using namespace std::chrono_literals; // cambiar

// verificar cuando lo implementemos que si ya ha spawneado un objeto que no se cree otro
struct SpawnerComponent : ECS::Component{

    using clk = std::chrono::steady_clock;
    // pondria explicit AIComponent(std::size_t eID = 7) en este caso, asi no tengo que pasarle el valor de la id
    explicit SpawnerComponent(std::size_t eID) : ECS::Component(eID){};

    static std::size_t getComponentTypeID() noexcept{
        return static_cast<std::size_t>(15);
    }

    // std::function<void(void)> spawnMethod {}; // creo una funcion como variable, void constSpawnerComponent&
    std::function<void(const SpawnerComponent&)> spawnMethod {};
    clk::time_point last_spawn_time { clk::now() };
    std::chrono::duration<double> spawn_interval { 3s }; // el namespace sirve para esto, para poner 5segundos literal
    std::size_t to_be_spawned { 2 };
    // bool spawneable { true }; // por si es spawneable
};