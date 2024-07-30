// managers
#include <game/man/gamemanager.hpp>   // el levelmanager esta aqui
#include <game/man/puzzlemanager.hpp> // singlecomponent
// puzzles
#include <game/puzzles/puzzlePilares.hpp>
// cmp
#include <game/cmp/HUD/HUDComponent.hpp> // singlecomponent
#include <game/cmp/cinematicComponent.hpp>
// libs
#include <iostream>
#include <algorithm>
#include <thread>
// #include <raylib.h>

// TODO: HACER a este un eventOBserver para poder cambiar de nivel y tal
LevelManager::LevelManager(StateManager &sm, AudioEngine &audioEngine, GraphicEngine &ge) : SM{sm}, audio{audioEngine}, GE{ge}
{
    // inicializacion
    EntityMan.addSingletonComponent<EventManager>();
    EntityMan.addSingletonComponent<PuzzleManager>();
    EntityMan.addSingletonComponent<HUDComponent>();
    EntityMan.addSingletonComponent<CinematicComponent>();
    EntityMan.addSingletonComponent<BlackBoardComponent>();

    GE.closeImGui();
    GE.initImGui_ = false;

    GE.endScene();
    GE.disableDrawModels();
    img = GE.addSceneImage("./media/img/cargando.png", 800, 820);
    GE.drawAll();
}

void LevelManager::update()
{
    auto current_time = std::chrono::steady_clock::now();

    if (update_new_level)
    {
        GE.closeImGui();
        GE.initImGui_ = false;
        // carga el primer mapa, tiene que cargar todos
        // GE.endScene();
        LoadLevel();
        update_new_level = false;
        last_time = current_time;
    }

    if (current_time - last_time >= loading_cooldown)
    {
        // std::cout << "tiempo pasado:" << loading_cooldown << "\n";
        // GE.clearImage(img);
        SM.pushState<GameManager>(SM, EntityMan, GOF, audio, EntityMan.getSingletonComponentEM<PuzzleManager>(), GE);
        m_alive = false;
        last_time = current_time;
    }

    timer.waitUntil_ns(NSPF);
    timer.start();
}

void LevelManager::LoadLevel()
{
    audio.stopAll();
    nlohmann::json datos_general;
    datos_general = manageData.leerJSON("./media/levels/general.json");
    currentLvl = datos_general["jugador"]["nivel_siguiente"];

    GE.clearModels();

    SaveGeneralData();
    pfsys.loadLevelWaypoints(currentLvl);
    GOF.initBehaviourTrees();
    GOF.initLevel(niveles[currentLvl]);
    GOF.initPuzzlesLevel(niveles[currentLvl]);
    GOF.initMessagesLevel(niveles[currentLvl]);
    ECS::currentlevel++;
}

void LevelManager::SaveGeneralData()
{
    // sobra el nivel_Actual, cambair solo a nivel_sigueinte
    nlohmann::json datos;
    datos["jugador"]["nivel_siguiente"] = currentLvl;
    datos["jugador"]["nivel_actual"] = niveles[currentLvl];
    lastLevel = currentLvl;
    lastLevel--;
    lastLevel = std::clamp(lastLevel, 0, static_cast<int>(niveles.size() - 1));
    datos["jugador"]["nivel_anterior"] = niveles[lastLevel];
    manageData.escribirJSON(datos, "./media/levels/general.json");
}