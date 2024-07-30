#pragma once
// states
#include <game/states/state.hpp>
// man
#include <game/man/levelmanager.hpp>
// sonido
#include <engines/audio/AudioEngine.hpp>
// libs
#include <array>
// util
#include <ecs/util/globals.hpp>
// #include <raylib.h>
//  Graphic
#include <engines/graphic/GraphicEngine.hpp>

constexpr glm::vec2 FULL_SCREEN{1920, 1080};
constexpr glm::vec2 WINDOW_SCREEN{1280, 720};
constexpr glm::vec2 CUATROCHENTA_SCREEN{854, 480};

struct SettingsState : StateBase
{
    explicit SettingsState(StateManager &sm, AudioEngine &audioEngine, GraphicEngine &ge) : SM{sm}, audio{audioEngine}, GE{ge}
    {
        GE.clearModels();

        resolutionList.push_back(WINDOW_SCREEN);
        resolutionList.push_back(FULL_SCREEN);
        resolutionList.push_back(CUATROCHENTA_SCREEN);
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

    UImage *button_backMenu{nullptr};
    UImage *button_arrowLeft{nullptr};
    UImage *button_arrowRigth{nullptr};

    std::vector<glm::vec2> resolutionList;
    int currentResolution{0};
    float posXInit{422};
    float posYInit{539};
};