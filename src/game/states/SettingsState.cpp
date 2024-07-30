#include <game/states/SettingsState.hpp>
#include <game/states/MenuState.hpp>

void SettingsState::update()
{
    GE.addSceneImage("./media/img/opciones.png", 460, 60);
    button_backMenu = GE.addSceneImage("./media/img/button_menu.png", 620, 800);
    button_arrowLeft = GE.addSceneImage("./media/img/leftArrow.png", 1230, 360);
    button_arrowRigth = GE.addSceneImage("./media/img/rigthArrow.png", 1350, 360);

    // std::cout << "Resolucion: " + std::to_string(static_cast<int>(resolutionList[currentResolution].x)) << std::endl;

    if (currentResolution > 2)
        currentResolution = 0;
    if (currentResolution < 0)
        currentResolution = 2;

    if (GE.buttonClick(button_backMenu->getPosition().x, button_backMenu->getPosition().y, button_backMenu->getWidth(), button_backMenu->getHeigth()))
    {
        GE.addSceneImage("./media/img/selected.png", 550, 760);
        GE.addSceneImage("./media/img/button_menu.png", 620, 800);
        if (GE.isMouseReleased())
        {
            GE.disableDrawModels();
            SM.pushState<MenuState>(SM, GE);
            m_alive = false;
        }
    }

    if (GE.buttonClick(button_arrowLeft->getPosition().x, button_arrowLeft->getPosition().y, button_arrowLeft->getWidth(), button_arrowLeft->getHeigth()))
    {
        if (GE.isMouseReleased())
        {
            GE.resizeWindow(resolutionList[currentResolution].x, resolutionList[currentResolution].y);
            currentResolution--;
        }
    }

    if (GE.buttonClick(button_arrowRigth->getPosition().x, button_arrowRigth->getPosition().y, button_arrowRigth->getWidth(), button_arrowRigth->getHeigth()))
    {
        if (GE.isMouseReleased())
        {
            GE.resizeWindow(resolutionList[currentResolution].x, resolutionList[currentResolution].y);
            currentResolution++;
        }
    }

    GE.addSceneText("Resolucion: " + std::to_string(GE.getWindowWidth()) + "x" + std::to_string(GE.getWindowHeigth()), "Vintage.ttf", 520, 620, 2.0f, {1.0f, 1.0f, 1.0f});
    //GE.addSceneText("Volume: " + std::to_string(GE.getWindowWidth()) + "x" + std::to_string(GE.getWindowHeigth()), "Vintage.ttf", 520, 620, 2.0f, {1.0f, 1.0f, 1.0f});

    if (!GE.isRunning())
    {
        m_alive = false;
        SM.pushState<MenuState>(SM, GE);
    }

    GE.drawAll();
    GE.endScene();

    timer.waitUntil_ns(NSPF);
    timer.start();
}