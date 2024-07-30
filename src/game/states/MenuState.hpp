#pragma once
// states
#include <game/states/state.hpp>
// audio
#include <engines/audio/AudioEngine.hpp>
// util
#include <game/util/GameDataManager.hpp>
#include <ecs/util/globals.hpp>
// libs
#include <array>
//#include <raylib.h>
// graphic
#include <engines/graphic/GraphicEngine.hpp>

struct MenuState : StateBase
{
    explicit MenuState(StateManager &sm, GraphicEngine &ge);

    void update() final;

    bool alive() final { return m_alive; }

private:
    StateManager &SM;
    GraphicEngine &GE;

    // audio
    std::unique_ptr<AudioEngine> audioEngine;

    bool m_alive{true};

    uint64_t FPS{60};
    uint64_t NSPF{1000000000 / FPS};
    GameTimer timer;
    GameDataManager manageData;

    UImage* button_play{nullptr};
    UImage* button_setting{nullptr};
    UImage* button_exit{nullptr};

    bool do_once{false};
};