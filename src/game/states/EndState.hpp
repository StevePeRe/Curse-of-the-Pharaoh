#pragma once
// states
#include <game/states/state.hpp>
// libs
#include <array>
//#include <raylib.h>
// Graphic
#include <engines/graphic/GraphicEngine.hpp>
// struct FmodEngine;

struct EndState : StateBase
{
    explicit EndState(StateManager &sm, GraphicEngine &ge) : SM{sm}, GE{ge}
    {
        //GE.clearUserInterface();
        GE.clearModels();
    }

    void update() final;

    bool alive() final { return m_alive; }

private:
    [[maybe_unused]]StateManager &SM;
    GraphicEngine &GE;
    bool m_alive{true};

    uint64_t FPS{60};
    uint64_t NSPF{1000000000 / FPS};
    GameTimer timer;

    UImage* button_backMenu{nullptr};
};