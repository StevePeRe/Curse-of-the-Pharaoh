// raiz
#include <game/states/MenuState.hpp>
// managers
#include <game/man/levelmanager.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <iostream>
// #include <raygui.h>
#include <cstdlib>
// state
#include <game/states/SettingsState.hpp>

// audio
#include <engines/audio/FMODEngine.hpp>

MenuState::MenuState(StateManager &sm, GraphicEngine &ge) : SM{sm}, GE{ge}
{

    audioEngine = std::make_unique<FMODEngine>();
    // EMPIEZA LA MUSICA
    audioEngine->init();

    auto *music = audioEngine->createInstance("Menu Music", "Musica/desert music");
    music->Play();

    audioEngine->createInstance("Hover Option", "Menus/menu_option");
    audioEngine->createInstance("Select Option", "Menus/menu_select");

    audioEngine->update();

    // audioEngine->createInstance("Nivel 1 Music", "NOMBRE-MUSICA-FMOD");
    // audioEngine->createInstance("Nivel 2 Music", "NOMBRE-MUSICA-FMOD");
    // audioEngine->createInstance("Nivel final Music", "NOMBRE-MUSICA-FMOD");

    // PARA CAMBIAR DE CANCION:
    //   En el cambio de nivel, poner:
    //       audioEngine->stopAll();
    //       audioEngine->getInstances("Nivel X Music")[0]->Play();

    // GE.addSceneImage("./media/img/fondo.png", 0, 0);
    button_play = GE.addSceneImage("./media/img/button_play.png", 620, 400);
    button_setting = GE.addSceneImage("./media/img/button_settings.png", 620, 590);
    button_exit = GE.addSceneImage("./media/img/button_exit.png", 620, 800);
}

void MenuState::update()
{

    /* audioEngine->update(); */

    GE.addSceneImage("./media/img/fondo.png", 0, 0);
    button_play = GE.addSceneImage("./media/img/button_play.png", 620, 400);
    button_setting = GE.addSceneImage("./media/img/button_settings.png", 620, 590);
    button_exit = GE.addSceneImage("./media/img/button_exit.png", 620, 800);

    if (GE.buttonClick(button_play->getPosition().x, button_play->getPosition().y, button_play->getWidth(), button_play->getHeigth()))
    {
        /* if(!(audioEngine->getInstances("Hover Option")[0]->Play().GetState() ==  AudioInstance::AudioState::PLAYING)){
            audioEngine->getInstances("Hover Option")[0]->Play();
        } */
        // efecto mouse hover
        GE.addSceneImage("./media/img/selected.png", 550, 370);
        GE.addSceneImage("./media/img/button_play.png", 620, 400);
        if (GE.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            audioEngine->getInstances("Select Option")[0]->Play();
            m_alive = false;
            // GE.clearUserInterface();
            GE.endScene();
            SM.pushState<LevelManager>(SM, *audioEngine.get(), GE);
        }
    }

    if (GE.buttonClick(button_setting->getPosition().x, button_setting->getPosition().y, button_setting->getWidth(), button_setting->getHeigth()))
    {
        GE.addSceneImage("./media/img/selected.png", 550, 560);
        GE.addSceneImage("./media/img/button_settings.png", 620, 590);
        // efecto mouse hover
        if (GE.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            audioEngine->getInstances("Select Option")[0]->Play();
            m_alive = false;
            // GE.clearUserInterface();
            GE.endScene();
            SM.pushState<SettingsState>(SM, *audioEngine.get(), GE);
        }
    }

    if (GE.buttonClick(button_exit->getPosition().x, button_exit->getPosition().y, button_exit->getWidth(), button_exit->getHeigth()))
    {
        GE.addSceneImage("./media/img/selected.png", 550, 760);
        GE.addSceneImage("./media/img/button_exit.png", 620, 800);
        // efecto mouse hover
        if (GE.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            audioEngine->getInstances("Select Option")[0]->Play();
            m_alive = false;
        }
    }

    button_play = nullptr;
    button_setting = nullptr;
    button_exit = nullptr;

    if (!GE.isRunning())
    {
        m_alive = false;
    }

    audioEngine->update();

    GE.drawAll();
    GE.endScene();

    timer.waitUntil_ns(NSPF);
    timer.start();
}