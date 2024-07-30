// raiz
#include <game/states/PauseState.hpp>
// managers
#include <game/man/gamemanager.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <iostream>
#include <cstdlib>
// #include <raygui.h>

void PauseState::update()
{
    // BeginDrawing();
    // ClearBackground(RAYWHITE);
    // GE.drawAll();
    // GE.endScene();

    GE.addSceneImage("./media/img/pausa.png", 460, 80);
    button_continue = GE.addSceneImage("./media/img/button_continue.png", 620, 500);
    button_backMenu = GE.addSceneImage("./media/img/button_menu.png", 620, 750);

    if (GE.buttonClick(button_continue->getPosition().x, button_continue->getPosition().y, button_continue->getWidth(), button_continue->getHeigth()))
    {
        GE.addSceneImage("./media/img/selected.png", 550, 470);
        GE.addSceneImage("./media/img/button_continue.png", 620, 500);
        if (GE.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            m_aliveP = false;
        }
    }

    if (GE.buttonClick(button_backMenu->getPosition().x, button_backMenu->getPosition().y, button_backMenu->getWidth(), button_backMenu->getHeigth()))
    {
        GE.addSceneImage("./media/img/selected.png", 550, 710);
        GE.addSceneImage("./media/img/button_menu.png", 620, 750);
        if (GE.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            GE.closeImGui();

            SM.pushState<MenuState>(SM, GE);
            gameMan.setNotAlive();
            gameMan.eraseData();

            GE.clearModels();

            audio.getInstances("Menu Music")[0]->Stop();

            m_aliveP = false;
        }
    }

    // GE.drawAll();
    // GE.endScene();

    if (!GE.isRunning())
    {
        m_aliveP = false;
    }

    GE.drawAll();
    GE.endScene();

    timer.waitUntil_ns(NSPF);
    timer.start();
}
