// #define RAYGUI_IMPLEMENTATION
// states
#include <game/states/MenuState.hpp>
#include <engines/graphic/GraphicEngine.hpp>

int main()
{
    try
    {

        //InitWindow(ECS::ANCHOPANTALLA, ECS::ALTOPANTALLA, ECS::TITLE);
        GraphicEngine GE{ECS::TITLE, 1280, 720, false};
        //SetTargetFPS(ECS::FPS);

        StateManager SM;
        //SM.pushState<MenuState>(SM);
        SM.pushState<MenuState>(SM, GE);
        //GE.addSceneCamera({0.0f,0.0f,0.0f});

        // auto emisor = GE.addSceneParticleEmiter({0.0f,0.0f,1.0f}, 1, 0, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f}, {0.1f,0.1f,0.1f});
        // auto affector = std::make_unique<AffectorDirection>(glm::vec3{0.0f,1.0f,0.0f}, 0.1f);
        // GE.getNode(emisor)->getEntity<T_EParticleEmiter>()->pushAffector(std::move(affector));
        //GE.fullScreenWindow();

        while (SM.alive() && GE.isRunning())
        {            
            SM.update();

            // GE.drawAll();

            // GE.endScene();
        }
    }
    catch (...)
    {
        std::cout << "Capturado: Error al ejecutar el juego\n";
    }

    return 0;
}