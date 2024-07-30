// raiz
#include <game/states/EndState.hpp>
// managers
#include <game/man/gamemanager.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <iostream>
#include <cstdlib>
// #include <raygui.h>

void EndState::update()
{

    GE.addSceneImage("./media/img/loLograste.png", 460, 110);
    button_backMenu = GE.addSceneImage("./media/img/button_menu.png", 620, 400);

    if (GE.buttonClick(button_backMenu->getPosition().x, button_backMenu->getPosition().y, button_backMenu->getWidth(), button_backMenu->getHeigth()))
    {
        GE.addSceneImage("./media/img/selected.png", 550, 370);
        GE.addSceneImage("./media/img/button_menu.png", 620, 400);
        if (GE.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            SM.pushState<MenuState>(SM, GE);
            m_alive = false;

            GE.closeImGui();
        }
    }

    if (!GE.isRunning())
    {
        m_alive = false;
    }

    GE.drawAll();
    GE.endScene();

    timer.waitUntil_ns(NSPF);
    timer.start();
}