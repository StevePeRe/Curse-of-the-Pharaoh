#pragma once
// states
#include <game/states/state.hpp>
// man
/* #include <game/man/gamemanager.hpp> */
// sonido
#include <engines/audio/AudioEngine.hpp>
// libs
#include <array>
//#include <raylib.h>
// graphic
#include <engines/graphic/GraphicEngine.hpp>

struct GameManager;

struct PauseState : StateBase
{
    explicit PauseState(StateManager &sm, GameManager &gameManager, AudioEngine &audioEngine, GraphicEngine &ge) : SM{sm}, gameMan{gameManager}, audio{audioEngine}, GE{ge}
    {
        GE.disableDrawModels();
    }

    void update() final;
    
    bool alive() final { return m_aliveP; }

private:
    [[maybe_unused]]StateManager &SM;
    GraphicEngine &GE;
    GameManager &gameMan;
    AudioEngine &audio;
    bool m_aliveP{true};

    uint64_t FPS{60};
    uint64_t NSPF{1000000000 / FPS};
    GameTimer timer;

    UImage *button_continue{nullptr};
    UImage *button_backMenu{nullptr};
};