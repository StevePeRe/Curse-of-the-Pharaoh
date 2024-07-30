// #define RAYGUI_IMPLEMENTATION // si lo quito falla el juego xdd
// raiz
#include <game/states/DeathState.hpp>
// managers
#include <game/man/gamemanager.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <iostream>
// #include <raygui.h>
#include <cstdlib>

void DeathState::update()
{
    // BeginDrawing();
    // ClearBackground(RAYWHITE);
    // GE.drawAll();

    // GE.clearModels();

    GE.addSceneImage("./media/img/hasMuerto.png", 460, 110);
    button_reset = GE.addSceneImage("./media/img/button_restart.png", 620, 400);
    button_backMenu = GE.addSceneImage("./media/img/button_menu.png", 620, 590);

    // GE.drawText("HAS MUERTO", "Vintage.ttf", 250, 140, 5, {0.0f,0.0f,0.0f});

    // // primer boton
    // // TODO Graphic poner el fondo a los textos del menu
    // // DrawRectangle(250, 250, 300, 50, Fade(SKYBLUE, 0.5f));
    // // DrawRectangleLines(250, 250, 300, 50, BLUE);
    // GE.drawText("Reiniciar", "Vintage.ttf", 325, 260, 5, {0.0f,0.0f,0.0f});
    if (GE.buttonClick(button_reset->getPosition().x, button_reset->getPosition().y, button_reset->getWidth(), button_reset->getHeigth()))
    {
        GE.addSceneImage("./media/img/selected.png", 550, 370);
        GE.addSceneImage("./media/img/button_restart.png", 620, 400);
        // DrawRectangle(250, 250, 300, 50, Fade(BLUE, 0.3f));
        if (GE.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            // volver a intentarlo desde el mismo nivel
            GE.disableDrawModels();

            m_alive = false;
            SM.pushState<LevelManager>(SM, audio, GE);
            audio.getInstances("Menu Music")[0]->Stop();
            audio.getInstances("Menu Music")[0]->Play();

            GE.closeImGui();

            //GE.clearUserInterface();
        }
    }
    
    if (GE.buttonClick(button_backMenu->getPosition().x, button_backMenu->getPosition().y, button_backMenu->getWidth(), button_backMenu->getHeigth()))
    {
        GE.addSceneImage("./media/img/selected.png", 550, 560);
        GE.addSceneImage("./media/img/button_menu.png", 620, 590);
        // DrawRectangle(250, 320, 300, 50, Fade(BLUE, 0.3f));
        if (GE.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            GE.disableDrawModels();            
            // std::cout << "\nContinuo jugando\n";
            // llamada para parar la musica para que no suene doble
            SM.pushState<MenuState>(SM, GE);
            m_alive = false;
            audio.getInstances("Menu Music")[0]->Stop();

            //GE.closeImGui();
        }
    }

    // GE.drawAll();
    // GE.endScene();

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
