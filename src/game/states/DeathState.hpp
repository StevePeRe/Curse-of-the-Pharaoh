#pragma once
// states
#include <game/states/state.hpp>
// man
#include <game/man/levelmanager.hpp>
// sonido
#include <engines/audio/AudioEngine.hpp>
// libs
#include <array>
//#include <raylib.h>
// Graphic
#include <engines/graphic/GraphicEngine.hpp>

// struct FMODEngine;

struct DeathState : StateBase
{
    explicit DeathState(StateManager &sm, AudioEngine &audioEngine, GraphicEngine &ge) : SM{sm}, audio{audioEngine}, GE{ge}
    {
        /*         audio.init();
                audio.createMusicInstance("desert music");
                audio.playMusic(); */
        // BeginDrawing();
        // ClearBackground(RAYWHITE);
        // EndDrawing();
        // GE.drawAll();
        // GE.endScene();
        //GE.clearUserInterface();
        GE.clearModels();
    }

    void update() final;

    bool alive() final { return m_alive; }

private:
    StateManager &SM;
    bool m_alive{true};

    GraphicEngine &GE;
    AudioEngine &audio;

    uint64_t FPS{60};
    uint64_t NSPF{1000000000 / FPS};
    GameTimer timer;

    UImage *button_reset{nullptr};
    UImage *button_backMenu{nullptr};
};