#pragma once
// Managers
#include <ecs/man/entitymanager.hpp> // el entity.hpp aqui, hace falta para inicializar el EntityMnagaer
// Factories
#include <game/factories/gameobjectfactory.hpp> // dentro las libs de audio
// State
#include <game/states/state.hpp>
// utils
#include <ecs/util/globals.hpp>
// sonido
#include <engines/audio/AudioEngine.hpp>
// #include <game/util/GameTimer.hpp>
// util
#include <game/util/GameDataManager.hpp>
#include <game/ai/pf/pathFollowingSys.hpp>
// libs
#include <iostream>
#include <cstdlib>
#include <array>
#include <string>

struct PuzzleManager;
struct GraphicEngine;
struct UImage;

struct LevelManager : StateBase
{

    // se llamará solo una vez, 
    explicit LevelManager(StateManager &sm, AudioEngine &audioEngine, GraphicEngine &ge);

    void update() final;

    bool alive() final { return m_alive; }

    void LoadLevel();
    void LoadSavedLevel();
    void SaveGeneralData();

    std::array<std::string, 3> getNiveles(){ return niveles; };      

    bool update_new_level { true };
    bool loadSaved { false };

    // variables
    private:
    StateManager &SM; 
    GraphicEngine &GE;
    ECS::EntityManager EntityMan{}; // inicializado
    AudioEngine &audio;
    GameObjectFactory GOF { EntityMan, GE, audio}; // inicializado
    PathfollowingSys pfsys;

    int lastLevel{0};
    int currentLvl{0};
    std::array<std::string, 3> niveles = {"level_0", "level_1", "level_2"};
    
    bool m_alive { true };
    uint64_t FPS{60};
    uint64_t NSPF{1000000000 / FPS};
    GameTimer timer;
    GameDataManager manageData;
    uint64_t totalElementsLoaded{0};

    std::chrono::steady_clock::time_point last_time{};
    std::chrono::milliseconds loading_cooldown{5800};

    UImage *img{nullptr};
};