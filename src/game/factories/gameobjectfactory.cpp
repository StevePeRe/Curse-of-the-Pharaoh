// raiz
#include <game/factories/gameobjectfactory.hpp>
// managers
#include <ecs/man/entitymanager.hpp>  // ya esta el entity dentro
#include <game/man/puzzlemanager.hpp> // singlecomponent
// cmp
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/cameraComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
#include <game/cmp/colliderComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/healthComponent.hpp>
// #include <game/ai/include_all.hpp>
#include <game/cmp/inputComponent.hpp>
#include <game/cmp/doorComponent.hpp>
#include <game/cmp/spawnerComponent.hpp>
#include <game/cmp/elevatorComponent.hpp>
#include <game/cmp/switchComponent.hpp>
#include <game/cmp/messageComponent.hpp>
#include <game/cmp/puzzleComponent.hpp>
#include <game/cmp/audioComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/animationComponent.hpp>
#include <game/cmp/powerUpComponent.hpp>
// ia
#include <game/ai/bt/createTrees.hpp>
// puzzles
#include <game/puzzles/puzzlePilares.hpp>
#include <game/puzzles/puzzlePuente.hpp>
#include <game/puzzles/puzzleBotones.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// audio
#include <engines/audio/AudioEngine.hpp>
// util
#include <ecs/util/globals.hpp>
#include <game/util/LayerMask.hpp>
// #include <game/util/GameDataManager.hpp>
// Read txt
#include <fstream>
#include <JSON/src/json.hpp>
// libs
#include <ecs/util/globals.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <cassert>
#include <ratio>
#include <thread>
#include <algorithm>
#include <numbers>
#include <cmath>
#include <vector>
#include <random>
// Graphic
#include <engines/graphic/GraphicEngine.hpp>
#include <engines/graphic/AffectorDirection.hpp>
// #include "gameobjectfactory.hpp"

// PARA PONERLE GRAVEDAD A LOS OBJETOS DEL MAPA Y QUE COLISIONEN
// DEBEN TENER COMPONENTE DE BODY Y PHYSICS, EL DE PHYSICS TIENE QUE SER
// DE TIPO DYNAMIC, Y QUE SU USE_GRAVITY SEA TRUE, POR DEFECTO ES TRUE

void GameObjectFactory::initLevel(const std::string nivel)
{
    // JUGADOR PRINCIPAL, siempre el primero en crear
    loadModelsDataFromTxt("./media/levels/" + nivel + "/models.txt", {0.0f, 0.0f, 0.0f});
    // cargar los mensajes por nivel de momento aqui, luego ver si se pueden poner en l blender directamente y asginarlos por orden los strnings

    // se creara luego con el mapa
    // TRIGGERS
    // createTrigger(7.2f, /* 0.90f */ 1.3f, -114.46f, 1.3f, 1.3f, 1.3f, ECS::EntityType::INMUNITY);
    // createTrigger(7.2f, /* 0.90f */ 1.3f, -135.46f, 1.3f, 1.3f, 1.3f, ECS::EntityType::SHOTGUNMODE);

    // spawner
    // createSpawner(4.f, 0.01f, 4.f, ECS::EntityType::AMMO,
    //     [&](const SpawnerComponent& sp) {
    //         auto *e = m_EntMan.getEntityByID(sp.getEntityID());
    //         if(!e) return;
    //         auto* phy = e->getComponent<PhysicsComponent>();
    //         if(!phy) return;

    //         // [[maybe_unused]]auto& e = createObject(0.0f, /* 0.90f */0.2f, 0.0f, 0.45f, 0.25f /* 7.2f */, 0.45f, RED, ECS::EntityType::AMMO);
    //         /* [[maybe_unused]]auto& e_object =  */createObject(phy->x, phy->y, phy->z, 0.45f, 0.25f, 0.45f, RED, ECS::EntityType::AMMO);

    //         std::cout << "entro en lambda\n";
    //     }
    // );

    GE.addSceneCamera({ECS::CAMERA_TARGET.x, ECS::CAMERA_TARGET.y, ECS::CAMERA_TARGET.z}, 1, 5,
                      {ECS::CAMERA_POSITION.x, ECS::CAMERA_POSITION.y, ECS::CAMERA_POSITION.z});

    GE.addSceneCamera({ECS::CAMERA_TARGET.x, ECS::CAMERA_TARGET.y, ECS::CAMERA_TARGET.z}, 1, 5,
                      {ECS::CAMERA_POSITION.x, ECS::CAMERA_POSITION.y, ECS::CAMERA_POSITION.z});

    // GE.setActiveCamera(1);

    GE.addSceneSkyBox({"./media/textures/skybox/right.png",
                       "./media/textures/skybox/left.png",
                       "./media/textures/skybox/top.png",
                       "./media/textures/skybox/bottom.png",
                       "./media/textures/skybox/front.png",
                       "./media/textures/skybox/back.png"});

    // audio.createInstance("DOOR_OPEN", "Efectos/door_open");
    // audio.createInstance("DOOR_CLOSED", "Efectos/door_closed");

    if (nivel == "level_0")
    {
        // pruebas fisicas
        // createElevator(3.f, 0.f, -118.5f, 3.5, 0.5f, 3.8f, 9.8f, ECS::SwitchType::SWITCH_1, ECS::ElevatorDirection::DIR_Z);
        // createWall(-5.f, 2.f, -111.f, 8.f, 3.f, 3.f, GREEN, ECS::EntityType::PARED);
        // createObject4movement(0.f, 9.f, 2.f, 2.f, 2.f, 2.f, {1.f,0.f,0.f}, ECS::EntityType::BOX);
        // createObject4movement(-5.f, 2.f, -119.f, 1.f, 1.f, 1.f, GRAY, ECS::EntityType::BOX);
        // createObject4movement(-5.f, 15.f, -111.f, 3.f, 3.f, 3.f, ORANGE, ECS::EntityType::BOX);
        // createObject4movement(-5.f, 5.f, -105.f, 3.f, 3.f, 3.f, ORANGE, ECS::EntityType::BOX);
        // pruebas fisicas

        // crear pilar de practica para disparo
        // CREAR ENEMIGOS - PT ENTRE 0.4 Y 0.01
        // createEnemyZombie(    0.f, 3.f,  -2.f,   {1.0f,0.0f,0.0f},    SB::Seek,  bt1,  0.07f);
        // createEnemyZombie(    2.f, 2.f,  0.8f,   {1.0f,0.0f,0.0f},    SB::Pathfollowing,  bt1,  0.02f);
        // createEnemyMomiaLaberinto(    0.36f, 2.f,  -28.68f,   {1.0f,0.0f,0.0f},    SB::Pathfollowing,  bts.at(idTree),  0.07f);
        // ***************** DESCOMENTAR LINEA 1317 **************
        // createEnemyZombie(    -9.f,  3.0f,  8.9f,   GREEN,    SB::Seek,    bt2,  0.03f);
        // createEnemyZombie(    -9.f,  3.0f,  1.4f,   GREEN,    SB::Arrive,  bt3,  0.4f);
        /* createEnemyEscarabajo( -2.f,         -124.0f,   BLUE,     SB::Seek,    bt4,  0.3f);
        createEnemyEscarabajo( -2.f,         -123.f,   PINK,     SB::Arrive,  bt5,  0.15f);
        createEnemyEscarabajo(-9.f,        -3.1f,   BLUE,     SB::Seek,    bt6,  0.2f); */

        // std::cout << "Aqui vuelvo a entrar" << std::endl;
        // El de rigth tiene que ir invertido en photoshop

        /*  GE.addSceneBillboard("./media/img/F.png", 1, 0, {0.0f, 3.0f, 0.0f}); */

        // GE.addSceneLigth();

        // std::string fileName, std::string textureName, std::string materialName="./media/models/vida.mtl", glm::vec3 lightColor=glm::vec3{0.923f,0.729f,0.239f}, glm::vec3 lightDirection=glm::vec3{0.0f,1.5f,-1.0f}, float diffuse = 0.9f, float ambient=0.3f, float specular=0.6f
        GE.addSceneModel("./media/models/M_SueloMuerte.obj", "./media/textures/prueba_lava.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_0/P_Pared.obj", "./media/textures/prueba3_suelo.png", "./media/models/vida.mtl", {0.639f, 0.573f, 0.369f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        // GE.addSceneModel("./media/models/O_Puente.obj", "./media/textures/prueba2_puente.png", {0.647f, 0.165f, 0.165f});
        GE.addSceneModel("./media/models/S_Suelo.obj", "./media/textures/suelo4.png", "./media/models/vida.mtl", {0.639f, 0.573f, 0.369f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/T_Techo.obj", "./media/textures/prueba_techo2.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/P_Roca.obj", "./media/textures/roca-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/Vasija.obj", "./media/textures/Vasija4-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/Antorcha.obj", "./media/textures/antorcha-t.png", "./media/models/vida.mtl", {0.965f, 1.0f, 0.0f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/P_Arbol.obj", "./media/textures/arbol-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_0/P_Cartel.obj", "./media/textures/cartel-t.png", "./media/models/level_0/P_Cartel.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);

        createObject(-10.560400009155273f, 0.36281800270080566f, -23.468799591064453f, 0.4999999701976776f, 0.5f, 1.0f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/A_Municion.obj", "./media/textures/municion-t.png", {0.0f, 1.5707963705062866f, 0.0f}, ECS::EntityTAG::AMMO);
        createObject(11.772500038146973f, 0.5651559829711914f, -85.19120025634766f, 1.2309600114822388f, 0.6991450786590576f, 0.5238684415817261f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/curaG.obj", "./media/textures/curaG-t.png", {0.0f, 4.71238899230957f, 0.0f}, ECS::EntityTAG::BIG_HEAL);
        createObject(38.28596878051758f, 0.3643699288368225f, -45.730281829833984f, 0.357915997505188f, 0.357915997505188f, 0.4581829905509949f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/H_pastillas.obj", "./media/textures/patillas-t.png", {0.0f, -0.0f, 0.0f}, ECS::EntityTAG::SMALL_HEAL);
        createDoor(6.635610103607178f, 2.1915199756622314f, -89.92060089111328f, 3.0f, 4.699999809265137f, 0.20000000298023224f, {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::NO_TAG, ECS::EntityType::DOOR_NO_KEY, {0.0f, 4.7123889923095771238899230957f, 0.0f});
        // createEnemyZombie(0.9278249740600586f, 1.510581374168396f, -88.1261978149414f, {0.0f, 0.0f, 0.0f}, SB::Seek, bt1, 0.03f);

        // createSpawnFloor(28.485f,-0.009104f,-52.98f, 5.f, 0.5f, 11.6f, {0.647f, 0.165f, 0.165f}, ECS::EntityType::SUELO, "./media/models/O_Puente.obj", "./media/textures/prueba2_puente.png", {0.0f,0.0f,0.0f});

        
        audio.stopAll();
        auto *music_level = audio.createInstance("Menu Music", "Musica/desert music");
        music_level->Play();

        createCamera(ECS::ID_MOVABLE_CAM, 0.592054f, 4.25905f, 3.92445f, 0.421809f, -18.9074f, -18.3159f, -130.0f, 03.060f, 0.2f, 0.0f, 0.5f, 24.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::EAST, 75.15f, ECS::EntityType::CAMERA, ECS::EntityTAG::MOVIBLE_CAM);
        createCamera(ECS::ID_INIT_CAM, -0.0404705f, 4.25905f, 5.70433f, 0.953981f, -11.0183f, -22.5289f, 0.35252f, 0.019693f, -0.096889f, 9.0f, 2.f, 7.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(2, -3.0951f, 8.45905f, -4.44766f, -3.11843f, -23.5107f, -20.4945f, -3.248f, 0.f, -7.2685f, 2.0f, 2.f, 7.2f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(3, 0.296257f, 2.75905f, -27.2582f, 0.511246f, -5.67612f, 3.71833f, 0.43934f, 0.f, -16.128f, 9.f, 2.f, 10.2f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::EAST, 75.150f, ECS::EntityType::CAMERA);
        createCamera(4, -4.05646f, 4.85905f, -23.2198f, -26.7562f, -17.858f, -23.2911f, -8.3214f, 0.f, -23.197f, 6.f, 2.f, 5.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::WEST, 75.150f, ECS::EntityType::CAMERA);
        createCamera(5, 0.449679f, 3.65905f, -17.675f, 0.218407f, -7.22546f, -44.888f, 0.59897f, 0.f, -28.842f, 9.0f, 2.f, 14.4f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(6, 3.88263f, 4.25905f, -31.7137f, 22.4948f, -8.71205f, -31.962f, 10.709f, 0.f, -32.009f, 10.5f, 2.f, 8.5f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::SOUTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(7, 20.8357f, 4.25905f, -25.9741f, 20.6269f, -12.6847f, -53.2544f, 20.91f, 0.f, -34.202f, 9.2f, 2.f, 13.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 83.150f, ECS::EntityType::CAMERA);
        createCamera(8, 28.2144f, 5.75905f, -54.0875f, 28.1134f, -13.5681f, -28.4401f, 28.069f, 0.f, -44.295f, 23.0f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::EAST, 75.150f, ECS::EntityType::CAMERA);
        createCamera(9, 28.3595f, 8.75905f, -46.6898f, 28.3593f, -23.3555f, -62.7219f, 27.999f, 0.f, -52.996f, 23.0f, 2.f, 11.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(10, 41.1158f, 3.65905f, -39.5627f, 10.2613f, -5.2097f, -38.7296f, 38.226f, 0.f, -40.208f, 3.0f, 2.f, 2.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::WEST, 75.150f, ECS::EntityType::CAMERA);
        createCamera(11, 28.3879f, 4.55905f, -50.9083f, 28.1575f, -6.62706f, -81.0107f, 28.068f, 0.f, -62.917f, 23.0f, 2.f, 8.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(12, -2.7019f, 4.25905f, -71.0322f, 26.9208f, -8.12205f, -70.2994f, 12.917f, 0.f, -70.766f, 26.f, 2.f, 7.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::SOUTH, 75.15f, ECS::EntityType::CAMERA);
        createCamera(13, 5.98816f, 7.85905f, -75.0341f, 5.83074f, -16.8062f, -95.5995f, 6.6836f, 0.f, -81.984f, 14.0f, 2.f, 14.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.15f, ECS::EntityType::CAMERA);
    }
    else if (nivel == "level_1")
    {
        audio.stopAll();
        auto *music_level = audio.createInstance("Dungeon Music", "Musica/dark");
        music_level->Play();
        music_level->SetVolume(0.25f);
        // createEnemyZombie(    -7.8f,  1.2f,  52.5f,   {0.0f,0.0f,0.0f},    SB::Seek,  bt1,  0.07f);
        // Posiciones segun estan en el mapa
        // createEnemyEscarabajo(-7.8f, -50.5f, {0.0f, 0.0f, 0.0f}, SB::Seek, bt4, 0.3f);

        // createEnemyEscarabajo(0.0f, -4.5f, {0.0f, 0.0f, 0.0f}, SB::Arrive, bt3, 0.07f);
        // createEnemyEscarabajo(0.0f, -6.5f, {0.0f, 0.0f, 0.0f}, SB::Seek, bt4, 0.4f);

        // createEnemyEscarabajo(-7.8f, -52.5f, {0.0f, 0.0f, 0.0f}, SB::Arrive, bt1, 0.4f);
        // createEnemyEscarabajo(-7.8f, -51.5f, {0.0f, 0.0f, 0.0f}, SB::Arrive, bt2, 0.15f);
        // createEnemyEscarabajo(-7.8f, -54.5f, {0.0f, 0.0f, 0.0f}, SB::Seek, bt3, 0.2f);

        // GE.addSceneLigth();

        GE.addSceneModel("./media/models/level_1/P_Pared.obj", "./media/textures/prueba3_suelo.png", "./media/models/vida.mtl", {0.639f, 0.573f, 0.369f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/S_Suelo.obj", "./media/textures/suelo4.png", "./media/models/vida.mtl", {0.639f, 0.573f, 0.369f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.8f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Columna.obj", "./media/textures/pilar-t0.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Antorcha.obj", "./media/textures/antorcha-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 2.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Antorcha1.obj", "./media/textures/antorchaAzul-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Ataud.obj", "./media/textures/coffin-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/fondo.obj", "./media/textures/fondo.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/M_SueloMuerte.obj", "./media/textures/prueba_lava.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Mesa.obj", "./media/textures/mesa-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Silla.obj", "./media/textures/silla-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Vasija1.obj", "./media/textures/Vasija1-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Vasija2.obj", "./media/textures/Vasija2-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Vasija3.obj", "./media/textures/Vasija3-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Vasija4.obj", "./media/textures/Vasija4-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Caldero.obj", "./media/textures/caldero-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Mural.obj", "./media/textures/prueba3_pared.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_1/P_Cartel.obj", "./media/textures/cartel-t.png", "./media/models/level_1/P_Cartel.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);

        createCamera(ECS::ID_MOVABLE_CAM, 0.592054f, 4.25905f, 3.92445f, 0.421809f, -18.9074f, -18.3159f, -130.0f, 03.060f, 0.2f, 0.0f, 0.5f, 24.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::EAST, 75.15f, ECS::EntityType::CAMERA, ECS::EntityTAG::MOVIBLE_CAM);
        createCamera(ECS::ID_INIT_CAM, 0.121025f, 2.45905f, -9.2721f, 0.00104076f, -5.97612f, 21.7147f, 0.f, 0.f, 3.0574f, 4.0f, 2.f, 8.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(2, -4.51915f, 5.75905f, -6.18398f, 12.4491f, -12.2621f, -26.6453f, 0.f, 0.f, -14.092f, 14.0f, 2.f, 18.2f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(3, -5.53122f, 5.86004f, -19.3866f, -5.22014f, -14.3403f, -44.5816f, -5.2035f, 0.f, -27.154f, 3.0f, 2.f, 2.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(4, 3.08759f, 4.25905f, -22.7955f, 2.86796f, -10.1641f, -51.4882f, 3.616f, 0.f, -29.813f, 6.0f, 2.f, 7.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(5, 3.08759f, 4.25905f, -30.3044f, 3.99888f, -6.62546f, -60.5174f, 3.616f, 0.f, -36.924f, 6.0f, 2.f, 7.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(6, 3.08759f, 4.25905f, -38.3044f, 3.99888f, -6.62546f, -60.5174f, 3.616f, 0.f, -42.299f, 6.0f, 2.f, 5.5f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(7, 8.68345f, 6.05905f, -54.611f, -19.0934f, -10.0588f, -54.6982f, -2.9388f, 0.f, -56.858f, 20.0f, 2.f, 17.6f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(8, -27.5622f, 13.2591f, -62.7683f, 4.29621f, 9.2303f, -62.4004f, -17.21f, 10.3f, -62.178f, 15.0f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(9, -26.5956f, 12.9591f, -72.3752f, -26.715f, 2.37709f, -42.0545f, -26.718f, 10.3f, -64.202f, 3.0f, 2.f, 10.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(10, -33.7943f, 12.9591f, -72.5167f, -1.762f, 10.848f, -73.4283f, -24.414f, 10.3f, -72.606f, 9.0f, 2.f, 4.5f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(11, -31.897f, 12.6591f, -87.3259f, -31.2961f, 10.848f, -56.1059f, -31.581, 10.3f, -78.659f, 4.6f, 2.f, 15.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(12, -17.7546f, 13.5591f, -87.5592f, -49.2546f, 7.311f, -87.343f, -27.032f, 10.3f, -88.319f, 14.f, 2.f, 4.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(13, -22.7853f, 12.6591f, -72.4009f, -23.7726f, 10.848f, -104.408f, -22.585, 10.3f, -81.046f, 10.0f, 2.f, 4.5f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(14, -33.0241f, 14.6591f, -83.2435f, -55.0311f, -7.7286f, -83.0225f, -37.256, 10.3f, -83.809, 6.3f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(15, -39.6238f, 14.6591f, -83.1772f, -60.4344f, -8.79932f, -82.9682f, -43.655f, 10.3f, -83.809f, 6.3f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(16, -48.961f, 14.6591f, -82.5802f, -49.1656f, -10.384f, -101.37f, -47.385f, 10.3f, -83.809f, 1.0f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(17, -40.7697f, 14.9591f, -90.794f, -55.170f, -12.7453f, -90.6569f, -41.737f, 10.3f, -90.299f, 3.0f, 2.f, 10.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(18, -34.209f, 14.9591f, -96.5399f, -60.2373f, -3.451f, -96.361f, -40.183f, 10.3f, -96.728f, 11.5f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(19, -34.3647, 12.0591, -111.87, -34.7976, 3.934, -80.8035, -35.352f, 10.3f, -101.17f, 3.0f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(20, -46.73f, 14.3591f, -96.5076f, -67.784f, -8.89f, -96.363f, -48.142f, 10.3f, -96.728f, 4.0f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(21, -46.5232f, 13.4591f, -104.3f, -73.968f, -2.211f, -103.837f, -49.478f, 10.3f, -100.02f, 3.0f, 2.f, 4.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(22, -22.4584f, 13.7591f, -84.009f, 6.516f, 0.312f, -84.254f, -16.736f, 10.3f, -83.832f, 7.0f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(23, -14.056f, 13.259f, -83.780f, 14.918f, -0.587f, -84.025f, -8.013f, 10.3f, -83.832f, 10.0f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(24, -4.741f, 12.9591f, -84.159f, 25.5779f, 2.377f, -83.808f, -1.862f, 10.3f, -83.832f, 2.0f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(25, -7.040f, 13.2591f, -80.527f, -6.381f, 0.582f, -110.026f, -7.098f, 10.3f, -87.434f, 11.0f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(26, -7.220f, 13.2591f, -88.040f, -6.357f, 0.582f, -58.546f, -7.098f, 10.3f, -80.348f, 11.0f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);

        // boxes
        createObject4movement(-5.78f, 1.5f, -6.78f, 0.2f, 0.2f, 0.2f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::BOX, {0.f, 0.f, 0.f}, 125.f);

        // plataforma ascensor
        createDoor(-26.286100387573242f, 12.327300071716309f, -89.79840087890625f, 3.0f, 4.699999809265137f, 0.20000000298023224f, {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::KEY_2, ECS::EntityType::DOOR_KEY, {0.0f, 4.71238899230957f, 0.0f});
        createDoor(-17.880958557128906f, 12.363320350646973f, -83.91605377197266f, 0.20000000298023224f, 4.699999809265137f, 3.0f, {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::KEY_1, ECS::EntityType::DOOR_KEY, {0.0f, 3.1415927410125732f, 0.0f});
        createObject(-21.82830047607422f, 10.264273643493652f, -71.09400177001953f, 1.2f, 0.5f, 0.5f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/curaG.obj", "./media/textures/curaG-t.png", {0.0f, 1.5707963705062866f, 0.0f}, ECS::EntityTAG::BIG_HEAL);
        createObject(-5.365600109100342f, 0.41751450300216675f, -28.015899658203125f, 1.0f, 0.4999999701976776f, 0.5f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/A_Municion.obj", "./media/textures/municion-t.png", {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::AMMO);
        createObject(-32.057899475097656f, 10.14109992980957f, -70.87039947509766f, 1.0f, 0.4999999701976776f, 0.5f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/A_Municion.obj", "./media/textures/municion-t.png", {0.0f, 3.1415927410125732f, 0.0f}, ECS::EntityTAG::AMMO);
        createObject(-32.62160110473633f, 10.15719985961914f, -103.51000213623047f, 1.0f, 0.4999999701976776f, 0.5f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/A_Municion.obj", "./media/textures/municion-t.png", {0.0f, 3.1415927410125732f, 0.0f}, ECS::EntityTAG::AMMO);
        // createKey(-54.02180099487305f, 10.05237102508545f, -106.78874969482422f, 0.5296859860420227f, 0.16593800336122513f, 0.8787630319595337f, {0.0f, 0.0f, 0.0f}, static_cast<ECS::EntityType>(1), {1.570796251296997f, -0.0f, 0.0f}, "./media/models/L_Llave.obj", "./media/textures/llave.png");

        createSwitch(-12.79f, 1.355f, -58.558f, 0.299f, 0.245f, 0.302f, ECS::SwitchType::SWITCH_1, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, 4.71238899230957f, 0.0f});
        createSwitch(-14.126f, 11.584f, -64.071f, 0.299f, 0.245f, 0.302f, ECS::SwitchType::SWITCH_1, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, 3.1415927410125732f, 0.0f}); // del mismo tipo switch y ascensor
        createElevator(-11.162f, 0.25f, -62.206f, 3.5, 0.000001f, 3.8f, 9.8f, false, ECS::SwitchType::SWITCH_1, ECS::ElevatorDirection::DIR_Y, "./media/models/level_1/C_Ascensor.obj", "./media/textures/ascensor-t.png");
        createTrigger(2.760f, 0.654f, -49.851f, 1.f,1.f,1.f, ECS::EntityType::POWER_UP,  "./media/models/U_EscopetaPU.obj", "./media/textures/escopetaPU-t.png", {0.0f, 1.5f, -1.0f}, ECS::EntityTAG::SHOTGUNMODE);
    }   
    else if (nivel == "level_2")
    {
        audio.stopAll();

        auto m1 = createEnemyMomiaLaberinto(28.8f, 18.5f,  -50.5f,   {1.0f,0.0f,0.0f},    SB::Pathfollowing,  bt5,  0.07f);
        auto pc1 = m1.getComponent<PathComponent>();
        pc1->en1 = true;

        createEnemyMomiaLaberinto(28.8f, 18.5f, -31.3f, {1.0f, 0.0f, 0.0f}, SB::Pathfollowing, bt6, 0.1f);

        auto *music_level = audio.createInstance("Dungeon Music", "Musica/dark");
        music_level->Play();
        music_level->SetVolume(0.25f);

        /* createTrigger(10.9f, 2.f, 0.6f, 3.f,3.f,3.f, ECS::EntityType::CHANGEm_EXTERIOR);
        createTrigger(11.4f, 2.f, -8.5f, 3.f,3.f,3.f, ECS::EntityType::CHANGEm_DUNGEON); */
        GE.addSceneModel("./media/models/level_2/P_Pared.obj", "./media/textures/prueba3_suelo.png", "./media/models/vida.mtl", {0.639f, 0.573f, 0.369f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/S_Suelo.obj", "./media/textures/suelo4.png", "./media/models/vida.mtl", {0.71f, 0.651f, 0.302f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        // GE.addSceneModel("./media/models/level_2/P_Columna.obj", "./media/textures/pilar-t0.png", {0.647f, 0.165f, 0.165f});
        GE.addSceneModel("./media/models/level_2/P_Antorcha.obj", "./media/textures/antorcha-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Antorcha1.obj", "./media/textures/antorchaAzul-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Ataud.obj", "./media/textures/coffin-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/fondo.obj", "./media/textures/fondo.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/M_SueloMuerte.obj", "./media/textures/prueba_lava.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Mesa.obj", "./media/textures/mesa-t.png", "./media/models/vida.mtl", {0.71f, 0.651f, 0.302f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        // GE.addSceneModel("./media/models/level_2/P_Silla.obj", "./media/textures/silla-t.png", {1.0f, 0.0f, 0.0f});
        GE.addSceneModel("./media/models/level_2/P_Vasija1.obj", "./media/textures/Vasija1-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Vasija2.obj", "./media/textures/Vasija2-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Vasija3.obj", "./media/textures/Vasija3-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Vasija4.obj", "./media/textures/Vasija4-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        // GE.addSceneModel("./media/models/level_2/P_Caldero.obj", "./media/textures/caldero-t.png", {1.0f, 0.0f, 0.0f});
        GE.addSceneModel("./media/models/level_2/P_Candelabro.obj", "./media/textures/candelabero-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Cuerno.obj", "./media/textures/cuerno-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Hacha.obj", "./media/textures/hacha-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Lija.obj", "./media/textures/lija-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.9f, 0.9f);
        GE.addSceneModel("./media/models/level_2/P_Mazo.obj", "./media/textures/mazo1-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Mazo2.obj", "./media/textures/mazo2-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_PaloT.obj", "./media/textures/paloT-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Punzon1.obj", "./media/textures/punzon1-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Punzon2.obj", "./media/textures/punzon2-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Punzon3.obj", "./media/textures/punzon3-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Punzon4.obj", "./media/textures/punzon4-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Sarcofago1.obj", "./media/textures/sarcofago-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Sarcofago2.obj", "./media/textures/sarcofago-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Sierra1.obj", "./media/textures/sierra1-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Sierra2.obj", "./media/textures/sierra2-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Velas.obj", "./media/textures/velas-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);
        GE.addSceneModel("./media/models/level_2/P_Estanteria.obj", "./media/textures/estanteriaT.png", "./media/models/level_2/P_Estanteria.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.7f, 0.7f, 0.7f);

        //  GE.addSceneModel("./media/models/level_2/P_Mural.obj", "./media/textures/prueba3_pared.png", {1.0f, 0.0f, 0.0f});

        // createCamera(ECS::ID_MOVABLE_CAM, 43.2194f, 46.559f, -13.2657f, 43.155f, 15.5656f, -21.6773f, -130.0f, 03.060f, 0.2f, 0.0f, 0.5f, 24.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::EAST, 75.15f, ECS::EntityType::CAMERA);
        // createCamera(ECS::ID_INIT_CAM, -2.29527f, 3.05907f, -1.81311f, 26.3973f, -11.3641f, -2.05566f, 0.35252f, 0.019693f, -0.096889f, 9.0f, 2.f, 7.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 75.150f, ECS::EntityType::CAMERA);
        createCamera(ECS::ID_MOVABLE_CAM, 43.2194f, 46.559f, -13.2657f, 43.155f, 15.5656f, -21.6773f, -130.0f, 03.060f, 0.2f, 0.0f, 0.5f, 24.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::EAST, 60.f, ECS::EntityType::CAMERA, ECS::EntityTAG::MOVIBLE_CAM);
        createCamera(ECS::ID_INIT_CAM, -2.29527f, 3.05907f, -1.81311f, 26.3973f, -11.3641f, -2.05566f, 1.8085f, 0.f, -0.18069f, 6.f, 2.f, 4.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(2, 4.33814f, 2.15907f, -0.0494593f, 35.752f, -4.40276f, -1.25805f, 10.889f, 0.f, -0.18069f, 12.0f, 2.f, 4.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(3, 3.4971f, 3.65907f, -8.04498f, 30.9435f, -13.011f, -7.64054f, 12.889f, 0.f, -8.2324f, 16.5f, 2.f, 11.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(4, 4.11147f, 2.75907f, 12.9865f, 27.2342f, -5.67609f, -7.64214f, 12.205f, 0.f, 8.0147f, 16.0f, 2.f, 11.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(5, 33.7077f, 3.05907f, -13.2995f, 8.8654f, -3.81673f, 5.85599f, 27.717f, 0.f, -8.2324f, 12.f, 2.f, 11.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(6, 18.7256f, 1.85907f, 0.0393201f, 50.02f, -5.33017f, -0.538204f, 28.704f, 0.f, -0.2475f, 10.f, 2.f, 4.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(7, 29.0472f, 2.15907f, -0.284637f, 59.8574f, -6.89409f, 0.0711874f, 38.361f, 0.f, -0.2475f, 9.f, 2.f, 4.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(8, 34.1704f, 19.2591f, -0.334879f, 65.9884f, 14.9121f, -0.60393f, 42.537f, 18.371f, -0.40834f, 4.f, 2.f, 14.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(9, 43.8723f, 20.1591f, -0.150913f, 74.8542f, 11.7239f, -0.722703f, 49.508f, 18.371f, -0.40834f, 8.5f, 2.f, 14.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(10, 54.1175f, 20.4591f, 4.66495f, 75.959f, 13.2699f, -17.7543f, 59.316f, 18.371f, -1.8367f, 9.f, 2.f, 11.0f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(11, 63.0407f, 24.9591f, 1.67122f, 62.7843f, -4.68243f, 14.0273f, 62.552f, 18.371f, 5.5039f, 3.f, 2.f, 2.3f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(12, 63.0407f, 24.9591f, 1.67122f, 62.7843f, -4.68243f, 14.0273f, 62.552f, 18.371f, 5.5039f, 3.f, 2.f, 2.3f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(13, 60.066f, 18.3591f, -7.05251f, 61.974f, 8.69151f, -37.618f, 59.927f, 18.371f, -11.117f, 2.f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(14, 59.1813f, 18.0591f, -13.4866f, 90.3154f, 10.2453f, -12.5041f, 62.891f, 18.371f, -13.634f, 3.5f, 2.f, 1.5f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(15, 42.3402f, 21.0591f, 3.93328f, 41.6467f, 7.21263f, 32.9014f, 42.537f, 18.371f, 14.1f, 4.f, 2.f, 14.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(16, 42.2071f, 21.9591f, 19.5912f, 15.6276f, 3.93791f, 19.242f, 39.491f, 18.371f, 19.621f, 1.f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(17, 37.7344f, 20.1591f, 19.8219f, 69.1044f, 13.2832f, 19.8704f, 47.11f, 18.371f, 19.601f, 5.f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(18, 50.509f, 20.1591f, 34.8306f, 50.8893f, 11.1059f, 4.0207f, 50.307f, 18.371f, 26.152f, 2.3f, 2.f, 16.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(19, 52.8271f, 20.4591f, 31.9815f, 21.529f, 13.2698f, 32.2959f, 41.452f, 18.371f, 32.508f, 15.5f, 2.f, 2.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(20, 30.4476f, 24.3591f, 42.5701f, 58.5234f, 13.4747f, 31.4067f, 42.749f, 18.371f, 38.994f, 24.f, 2.f, 8.5f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(21, 38.4867f, 22.5591f, 34.6425f, 38.0612f, 12.5857f, 65.1664f, 38.273f, 18.371f, 53.844f, 15.f, 2.f, 15.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(22, 37.1971f, 23.4591f, 55.8035f, 37.1796f, 1.43314f, 79.1749f, 38.273f, 18.371f, 60.942f, 15.f, 2.f, 4.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(23, 30.5803f, 4.25907f, 53.3813f, 52.3809f, -6.32275f, 32.3072f, 41.128f, 0.35556f, 41.208f, 22.f, 2.f, 25.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(24, 31.2637f, 21.0591f, 18.171f, 46.571f, 6.06494f, 42.0921f, 32.409f, 18.371f, 31.453f, 2.f, 2.f, 5.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(25, 41.9403f, 20.1591f, -7.28114f, 17.2423f, 10.7983f, 10.9873f, 35.754f, 18.371f, -0.40834f, 9.f, 2.f, 14.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(26, 42.9607f, 23.3591f, -7.86355f, 42.809f, -0.91209f, -27.6802f, 42.926f, 18.371f, -10.948f, 12.f, 2.f, 4.7f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(27, 28.8428f, 19.5591f, -10.1556f, 51.2077f, 14.5766f, -32.6576f, 32.558f, 18.371f, -14.618f, 8.f, 2.f, 10.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(28, 57.0409f, 20.1591f, -8.64405f, 34.915f, 16.1306f, -31.5694f, 53.235f, 18.371f, -14.608f, 8.f, 2.f, 10.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(29, 38.7517f, 19.5591f, -9.03136f, 38.5157f, 10.5059f, -39.8427f, 38.515f, 18.371f, -16.635f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(30, 47.4468f, 20.4591f, -9.69796f, 47.2089f, 12.3342f, -40.767f, 47.6f, 18.371f, -16.635f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(31, 28.4532f, 18.6591f, -19.6896f, 50.2762f, 15.2685f, -43.0051f, 32.143f, 18.371f, -24.788f, 9.f, 2.f, 9.5f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(32, 43.1643f, 24.559f, -20.4655f, 43.1196f, -3.03102f, -26.2464f, 42.926f, 18.371f, -21.533f, 12.f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(33, 57.2005f, 19.2591f, -19.6064f, 35.8713f, 12.3832f, -42.6096f, 53.756f, 18.371f, -24.858f, 9.f, 2.f, 10.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(34, 38.3851f, 19.8591f, -17.7288f, 38.1485f, 11.1145f, -48.6292f, 38.515f, 18.371f, -26.415f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(35, 47.6323f, 19.5591f, -18.4121f, 48.025f, 15.2121f, -50.2288f, 47.384f, 18.371f, -26.415f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(36, 28.5885f, 19.2591f, -29.1527f, 50.7273f, 14.2766f, -51.8772f, 32.143f, 18.371f, -34.769f, 9.f, 2.f, 10.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(37, 43.0908f, 24.659f, -30.0652f, 42.9962f, -1.98242f, -42.4235f, 42.926f, 18.371f, -31.262f, 14.f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(38, 57.1416f, 19.2591f, -28.2894f, 37.6917f, 14.9121f, -53.4719f, 53.756f, 18.371f, -34.627f, 7.f, 2.f, 9.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(39, 38.6093f, 19.8591f, -27.6308f, 38.3714f, 11.7342f, -58.6999f, 38.509f, 18.371f, -36.067f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(40, 47.4121f, 20.1591f, -26.7876f, 47.4858f, 13.5972f, -58.2246f, 47.343f, 18.371f, -36.067f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(41, 28.7008f, 18.9591f, -38.8047f, 49.4854f, 12.3972f, -62.3907f, 32.143f, 18.371f, -44.997f, 9.f, 2.f, 10.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(42, 43.315f, 24.659f, -39.9672f, 43.2625f, -3.7161f, -46.8193f, 42.926f, 18.371f, -40.906f, 12.f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(43, 57.1428f, 19.2591f, -38.1954f, 39.6123f, 13.6432f, -64.5108f, 53.75f, 18.371f, -44.09f, 9.f, 2.f, 9.5f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(44, 38.5358f, 20.7591f, -37.2306f, 39.2367f, 13.8832f, -68.5928f, 38.509f, 18.371f, -45.739f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(45, 47.5379f, 19.2591f, -36.9995f, 47.2942f, 14.9121f, -68.8176f, 47.343f, 18.371f, -45.644f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(46, 28.5838f, 19.2591f, -48.7876f, 50.6487f, 13.6431f, -71.4362f, 32.143f, 18.371f, -53.699f, 9.f, 2.f, 7.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(47, 42.6415f, 24.059f, -49.5624f, 42.5771f, -3.93441f, -57.974f, 42.926f, 18.371f, -50.66f, 12.f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(48, 57.0607f, 18.9591f, -48.2334f, 39.6316f, 12.3972f, -74.3967f, 53.648f, 18.371f, -52.769f, 9.f, 2.f, 7.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(49, 38.7646f, 19.8591f, -46.5326f, 38.5198f, 16.788f, -78.4992f, 38.509f, 18.371f, -55.607f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(50, 47.4644f, 21.0591f, -46.5992f, 47.2314f, 10.781f, -77.0239f, 47.343f, 18.371f, -55.634f, 2.5f, 2.f, 6.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(51, 29.3548f, 19.8591f, -62.0858f, 50.3709f, 16.1492f, -38.0876f, 32.103f, 18.371f, -59.504f, 9.f, 2.f, 4.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(52, 43.1703f, 24.659f, -58.8667f, 43.1059f, -3.33441f, -67.2783f, 42.729f, 18.371f, -60.321f, 12.f, 2.f, 3.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(53, 57.0045f, 19.5591f, -61.9614f, 35.0241f, 14.8941f, -39.0169f, 53.403f, 18.371f, -58.663f, 9.f, 2.f, 4.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);
        createCamera(54, 27.8193f, 2.75907f, 1.77116f, 28.0897f, -10.5051f, 31.0173f, 27.717f, 0.f, 8.247f, 13.f, 2.f, 11.f, {0.0f, 0.0f, 0.0f}, ECS::ORIENTATION::NORTH, 60.f, ECS::EntityType::CAMERA);

        // createSwitch(-12.4f, 2.f, 60.18f, .5f, 0.8f, .5f, ECS::SwitchType::SWITCH_1);
        // createSwitch(-12.4f, 2.f, 60.18f, .5f, 0.8f, .5f, ECS::SwitchType::SWITCH_2);

        createKey(27.4545f, -1.01856f, 12.0866f, 0.5296859860420227f, 0.16593800336122513f, 0.8787630319595337f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, {0.0f, 0.0f, 4.71238899230957f}, "./media/models/L_Llave.obj", "./media/textures/llave.png", ECS::EntityTAG::KEY_3);
        createKey(43.3184f, 17.6655f, -41.147f, 0.5296859860420227f, 0.16593800336122513f, 0.8787630319595337f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, {0.0f, 0.0f, 4.71238899230957f}, "./media/models/L_Llave.obj", "./media/textures/llave.png", ECS::EntityTAG::KEY_2);
        createKey(33.835f, -1.003f, 35.876f, 0.5296859860420227f, 0.16593800336122513f, 0.8787630319595337f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, {0.0f, 0.0f, 4.71238899230957f}, "./media/models/L_Llave.obj", "./media/textures/llave.png", ECS::EntityTAG::KEY_4);
        createKey(63.751f, 17.3778f, -13.5396f, 0.5296859860420227f, 0.16593800336122513f, 0.8787630319595337f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, {0.0f, 0.0f, 4.71238899230957f}, "./media/models/L_Llave.obj", "./media/textures/llave.png", ECS::EntityTAG::KEY_1);

        createDoor(27.962f, 1.36679f, 1.9382f, 3.0f, 4.699999809265137f, 0.20000000298023224f, {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::KEY_2, ECS::EntityType::DOOR_KEY, {0.0f, 1.5707963705062866f, 0.0f});
        createDoor(42.1951f, 19.6461f, -8.09511f, 3.0f, 4.699999809265137f, 0.20000000298023224f, {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::KEY_1, ECS::EntityType::DOOR_KEY, {0.0f, 4.71238899230957f, 0.0f});
        createDoor(42.1951f, 19.6461f, 7.15687f, 3.0f, 4.699999809265137f, 0.20000000298023224f, {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::KEY_3, ECS::EntityType::DOOR_KEY, {0.0f, 1.5707963705062866f, 0.0f});
        createDoor(30.736f, 19.709f, -0.301f, 0.20000000298023224f, 4.699999809265137f, 3.0f, {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::KEY_4, ECS::EntityType::DOOR_KEY, {0.0f, 0.0f, 0.0f});

        createObject(19.5503f, -0.8213085f, 9.12933f, 0.5f, 0.4999999701976776f, 1.0f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/A_Municion.obj", "./media/textures/municion-t.png", {0.0f, 4.71238899230957f, 0.0f}, ECS::EntityTAG::AMMO);
        createObject(42.5237f, 17.564f, -21.2569f, 1.0f, 0.4999999701976776f, 0.5f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/A_Municion.obj", "./media/textures/municion-t.png", {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::AMMO);
        createObject(33.4099f, 17.564f, -60.6055f, 1.0f, 0.4999999701976776f, 0.5f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/A_Municion.obj", "./media/textures/municion-t.png", {0.0f, 0.0f, 0.0f}, ECS::EntityTAG::AMMO);
        createObject(63.8734f, 17.564f, 5.24569, 0.5f, 0.4999999701976776f, 1.0f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/A_Municion.obj", "./media/textures/municion-t.png", {0.0f, 4.71238899230957f, 0.0f}, ECS::EntityTAG::AMMO);
        createObject(33.6341f, 17.6655f, -31.1144f, 1.2f, 0.5f, 0.5f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/curaG.obj", "./media/textures/curaG-t.png", {0.0f, 4.71238899230957f, 0.0f}, ECS::EntityTAG::BIG_HEAL);
        createObject(51.6824f, 17.6655f, -50.4538f, 1.2f, 0.5f, 0.5f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/curaG.obj", "./media/textures/curaG-t.png", {0.0f, 4.71238899230957f, 0.0f}, ECS::EntityTAG::BIG_HEAL);
        createObject(35.4226f, 17.6655f, 19.6351f, 0.5f, 0.5f, 1.2f, {0.0f, 0.0f, 0.0f}, ECS::EntityType::PICKABLE_OBJECT, "./media/models/curaG.obj", "./media/textures/curaG-t.png", {0.0f, 3.1415927410125732f, 0.0f}, ECS::EntityTAG::BIG_HEAL);

        createSwitch(39.056f, 0.49748f, 1.6689f, 0.299f, 0.245f, 0.302f, ECS::SwitchType::SWITCH_1, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, 0.0f, 0.0f});
        createSwitch(38.8507f, 18.6717f, 6.5114f, 0.299f, 0.245f, 0.302f, ECS::SwitchType::SWITCH_1, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, 0.0f, 0.0f}); // del mismo tipo switch y ascensor
        createSwitch(54.4633f, 18.6717f, 36.6292f, 0.299f, 0.245f, 0.302f, ECS::SwitchType::SWITCH_2, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, 1.5707963705062866f, 0.0f});
        createSwitch(52.017f, 0.8f, 35.4268f, 0.299f, 0.245f, 0.302f, ECS::SwitchType::SWITCH_2, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, 1.5707963705062866f, 0.0f}); // del mismo tipo switch y ascensor

        createElevator(42.707f, -1.23f, -0.29f, 4.16f, 0.5f, 4.16f, 18.27f, false, ECS::SwitchType::SWITCH_1, ECS::ElevatorDirection::DIR_Y, "./media/models/level_2/C_Ascensor1.obj", "./media/textures/ascensor-t.png");
        createElevator(49.125f, 17.1f, 40.459f, 6.0, 0.5f, 5.1f, 18.38f, true, ECS::SwitchType::SWITCH_2, ECS::ElevatorDirection::DIR_Y, "./media/models/level_2/C_Ascensor2.obj", "./media/textures/ascensor-t.png");
        createTrigger(44.38f, 17.517f, -12.385f, 1.f,1.f,1.f, ECS::EntityType::POWER_UP,  "./media/models/U_ArmorPU.obj", "./media/textures/armor-t.png", {0.0f, 1.5f, -1.0f}, ECS::EntityTAG::INMUNITY);

    }
}

void GameObjectFactory::initBehaviourTrees() 
{
    BehaviourTree bt;
    bts.clear();

    bts.push_back(bt1);
    bts.push_back(bt2);
    bts.push_back(bt3);
    bts.push_back(bt4);
    bts.push_back(bt5);
    bts.push_back(bt6);
    bts.push_back(bt7);
    bts.push_back(bt8);
    bts.push_back(bt9);
    bts.push_back(bt10);
    bts.push_back(bt11);
    bts.push_back(bt12);
    bts.push_back(bt13);
    bts.push_back(bt14);
    bts.push_back(bt15);
    bts.push_back(bt16);
    bts.push_back(bt17);
    bts.push_back(bt18);
    bts.push_back(bt19);
    bts.push_back(bt20);

    for (int i = 0; i < 20; i++)
    {
        bts.at(i)->clearNodes();
    }
}

// PUZZLES
void GameObjectFactory::initPuzzlesLevel(const std::string nivel)
{
    // leerlo mas facilmente con JSON
    // no poner dos puzles con el mismo nombre en le mismo nivel
    if (nivel == "level_0")
    {
        auto &puzzleMan = m_EntMan.getSingletonComponentEM<PuzzleManager>();
        // puzzle2
        puzzleMan.addPuzzle(ECS::PUZZLE_TYPE::PILARES, PuzzlePuenteNivel1{});                      // LO AÑADO
        createRangeCube4Puzzle(35.23f, 2.03f, -39.12f, 14.f, 5.f, 4.f, ECS::EntityType::PUZZLE_1); // RANGO PARA ACTIVAR PUZLE
        createObject4Puzzle(28.60f, 1.26f, -39.15f, 1.f, 2.f, 1.f, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::INTERACTION, "./media/models/Pilar_Target.obj", "./media/textures/pilarTarget-t.png");
        // createObject4Puzzle(24.3f, 1.23f, -82.2f, 2.0f, 4.0f, 2.0f, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::PILARES_1); // OBJETO INTERACTUABLE DEL PUZLE
    }
    else if (nivel == "level_1")
    {
        [[maybe_unused]] auto &puzzleMan = m_EntMan.getSingletonComponentEM<PuzzleManager>();
        // puzzle 1
        
        puzzleMan.addPuzzle(ECS::PUZZLE_TYPE::PILARES, PuzzlePilares{});

        createRangeCube4Puzzle(-6.5f, 12.03f, -86.4f, 13.f, 5.f, 11.f, ECS::EntityType::PUZZLE_1); // ESTO SI PONERLO EN EL TXT mientras, colisionara para activar el puzzle
        createObject4PuzzleClosely(-9.02f, 12.03f, -89.366f, 2.0f, 4.0f, 2.0f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::PILARES_1, "./media/models/level_1/acertijo-hombre.obj", "./media/textures/acertijo-hombre.png", {0.0f, 3.14f, 0.0f});
        createObject4PuzzleClosely(-4.39f, 12.03f, -89.366f, 2.0f, 4.0f, 2.0f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::PILARES_2, "./media/models/level_1/acertijo-musico.obj", "./media/textures/musico.png", {0.0f, 3.14f, 0.0f});
        createObject4PuzzleClosely(-9.02f, 12.03f, -79.462f, 2.0f, 4.0f, 2.0f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::PILARES_3, "./media/models/level_1/acertijo-hombre-bestia.obj", "./media/textures/acertijo-hombre-bestia.png", {0.0f, 3.14f, 0.0f});
        createObject4PuzzleClosely(-4.39f, 12.03f, -79.462f, 2.0f, 4.0f, 2.0f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::PILARES_4, "./media/models/level_1/acertijo_musico_bestia.obj", "./media/textures/musico_bestia.png", {0.0f, 3.14f, 0.0f});

        // puzle botones
        puzzleMan.addPuzzle(ECS::PUZZLE_TYPE::BOTONES, PuzzleBotones{});
        // creo uno gigante y ya
        createRangeCube4Puzzle(-43.92f, 11.03f, -96.02f, 25.f, 3.f, 27.f, ECS::EntityType::PUZZLE_2); // ESTO SI PONERLO EN EL TXT mientras, colisionara para activar el puzzle
        createObject4PuzzleClosely(-41.92f, 11.03f, -82.5f, 0.299f, 0.245f, 0.302f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_2, ECS::PUZZLE_TYPE::BOTONES_1, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, 0.0f, 0.0f});
        createObject4PuzzleClosely(-48.35f, 10.9f, -86.07f, 0.299f, 0.245f, 0.302f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_2, ECS::PUZZLE_TYPE::BOTONES_2, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, 1.57f, 0.0f});
        createObject4PuzzleClosely(-54.9f, 11.04f, -106.77f, 0.299f, 0.245f, 0.302f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_2, ECS::PUZZLE_TYPE::BOTONES_3, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, -1.57f, 0.0f});
        createObject4PuzzleClosely(-32.48f, 11.5f, -103.35f, 0.299f, 0.245f, 0.302f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_2, ECS::PUZZLE_TYPE::BOTONES_4, "./media/models/I_Palanca.obj", "./media/textures/palanca-t.png", {0.0f, 0.0f, 0.0f});
    }
    else if (nivel == "level_2")
    {
    }
}

// lo uso para crear objetos estaticos en el puzzle
ECS::Entity &GameObjectFactory::createObject4Puzzle(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::PUZZLE_TYPE type, ECS::PUZZLE_TYPE puzzleType, std::string fileName, std::string texture) const
{
    auto &e = m_EntMan.newEntity();
    // e.setType(type);
    auto &phy = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &ren = m_EntMan.addComponent<RenderComponent>(e);
    auto &puzzle = m_EntMan.addComponent<PuzzleComponent>(e);

    ren.node = GE.addSceneModel(fileName, texture, "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z});

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;

    puzzle.puzzle_type = type;
    puzzle.puzzle_object = puzzleType;

    phy.static_ = true;
    phy.invMass = 0; // si es estatico tiene que tener esta masa
    phy.position.x = x;
    phy.position.y = y;
    phy.position.z = z;
    phy.dimension = {w, h, d};
    phy.staticFriction = .85f;
    phy.dynamicFriction = .65f;
    phy.layer.AddLayer(LayerRaycast::ENVIRONMENT); // LO DEDUCE

    ren.w = w;
    ren.h = h;
    ren.d = d;
    ren.color = c;

    return e;
}

// lo uso para crear objetos estaticos en el puzzle
ECS::Entity &GameObjectFactory::createObject4PuzzleClosely(float x, float y, float z, float w, float h, float d, bool popUpE, glm::vec3 c, ECS::PUZZLE_TYPE type, ECS::PUZZLE_TYPE puzzleType, std::string fileName, std::string texture, glm::vec3 rotation) const
{
    auto &e = m_EntMan.newEntity();
    // e.setType(type);
    auto &phy = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &ren = m_EntMan.addComponent<RenderComponent>(e);
    auto &puzzle = m_EntMan.addComponent<PuzzleComponent>(e);
    auto &ms = m_EntMan.addComponent<MessageComponent>(e);

    ren.node = GE.addSceneModel(fileName, texture, "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z}, rotation);

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;

    puzzle.puzzle_type = type;
    puzzle.puzzle_object = puzzleType;

    phy.static_ = true;
    phy.invMass = 0; // si es estatico tiene que tener esta masa
    phy.position.x = x;
    phy.position.y = y;
    phy.position.z = z;
    phy.dimension = {w, h, d};
    phy.staticFriction = .85f;
    phy.dynamicFriction = .65f;
    phy.layer.AddLayer(LayerRaycast::TRIGGER);

    ren.w = w;
    ren.h = h;
    ren.d = d;
    ren.color = c;

    ms.justUsePopUpE = popUpE;

    return e;
}

// lo uso para crear el objeto que determina cuando el puzzle esta activo o no
ECS::Entity &GameObjectFactory::createRangeCube4Puzzle(float x, float y, float z, float w, float h, float d, ECS::EntityType type) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    auto &phy = m_EntMan.addComponent<PhysicsComponent>(e);
    /* auto& ren = m_EntMan.addComponent<RenderComponent>(e); */
    // auto& puzzle = m_EntMan.addComponent<PuzzleComponent>(e);

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    // body.collider = false;
    phy.layer.AddLayer(LayerRaycast::TRIGGER);

    phy.trigger = true;
    phy.position.x = x;
    phy.position.y = y;
    phy.position.z = z;
    // puzzle.puzzle_type = puzzleType;

    /* ren.w = w; ren.h = h; ren.d = d;
    ren.color = {0.0f,0.0f,0.0f}; */

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// MENSAJES
void GameObjectFactory::initMessagesLevel(const std::string nivel)
{
    // mensaje bienvenida
    // pasarle la variable cuando creo el mensaej si quiero que sea dialogo tocho o solo saber como se usa algo

    // CREAR CARTELES POR EL MAPA PARA QUE AYUDEN AL JUGADOR

    if (nivel == "level_0")
    {
        createMessage(0.f, 0.f, 0.f, 1.f, 2.f, 1.f, "Intenta abrirte camino cruzando los diferentes desafios que *encontraras. AYUDA: Mira tus utilidades con el TAB, recoge objetos *con la F y usa la rueda del raton para seleccionar tus objetos. *Buena suerte.");
        createMessage(-8.2f, 1.2f, -117.7f, 1.f, 2.f, 1.f, "AYUDA: Prueba a agacharte con el CTRL*");
        createMessage(-4.63f, 1.2f, -98.4f, 8.f, 2.f, 7.f, "AYUDA: Prueba a apuntar manteniendo el clic derecho y disparando *con el clic izquierdo.*");
        createMessage(33.4f, 1.2f, -82.3f, 3.f, 2.f, 3.f, "AYUDA: Pon en practica tu tiro y disparale al pilar de enfrente!*");
        createMessage(27.4f, 1.2f, -45.8f, 3.f, 2.f, 3.f, "SOLO SE PUEDE PASAR ACTIVANDO EL MECANICASMO DEL *PUENTE.");
    }
    else if (nivel == "level_1")
    {
        createMessage(0.092f, 1.2f, -2.66f, 1.f, 2.f, 1.f, "Muy bien! Has superado tu primer reto. Ahora se ha acabado lo facil. *Te intentare ayudar, pero creo que puedes tu solo.");
        createMessage(-7.3f, 1.2f, -60.f, 5.5f, 2.5f, 5.5f, "Prueba a pulsar la E para activar el ascensor que te llevara al *siguiente piso");

        // puzzle 1
        // El primero, temeroso de las bestias, no se atrevió a caminar el último
        createMessage(-1.52f, 10.96f, -86.298f, 1.5f, 2.5f, 10.5f, "El primero, temeroso de las bestias, no se atrevio a caminar el ultimo*El segundo al lado del primero, tocaba un triste lamento.*El tercero se mantenia cerca de su fiel bestia.*El cuarto no marchaba junto al primero, pero al igual que el segundo, *tocaba una cancion.");
        createMessage(-4.46f, 12.96f, -80.87f, .5f, 2.5f, .5f, "Estatua del musico y su bestia.");
        createMessage(-8.88f, 12.96f, -80.87f, .5f, 2.5f, .5f, "Estatua del hombre y su bestia.");
        createMessage(-8.89f, 12.96f, -87.7f, .5f, 2.5f, .5f, "Estatua del chico.");
        createMessage(-4.5f, 12.96f, -87.7f, .5f, 2.5f, .5f, "Estatua del musico.");

        createMessage(-11.9f, 10.96f, -83.5f, 2.5f, 2.f, 2.5f, "LOS PILARES SE ACTIVAN DE UNA FORMA MISTERIOSA ACERCANDOTE *A ELLOS.");

        createMessage(-33.02f, 11.f, -81.9f, 2.5f, 2.f, 2.5f, "El laberinto esconde secretos, que al ser resueltos puedes *ser recompensado.");
        // createObject4PuzzleClosely(-9.02f, 12.03f, -89.366f, 2.0f, 4.0f, 2.0f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::PILARES_1, "./media/models/level_1/acertijo-hombre.obj", "./media/textures/acertijo-hombre.png", {0.0f,3.14f,0.0f});
        // createObject4PuzzleClosely(-4.39f, 12.03f, -89.366f, 2.0f, 4.0f, 2.0f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::PILARES_2, "./media/models/level_1/acertijo-hombre.obj", "./media/textures/acertijo-hombre.png", {0.0f,3.14f,0.0f});
        // createObject4PuzzleClosely(-9.02f, 12.03f, -79.462f, 2.0f, 4.0f, 2.0f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::PILARES_3, "./media/models/level_1/acertijo-hombre-bestia.obj", "./media/textures/acertijo-hombre-bestia.png", {0.0f,3.14f,0.0f});
        // createObject4PuzzleClosely(-4.39f, 12.03f, -79.462f, 2.0f, 4.0f, 2.0f, true, {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PUZ_1, ECS::PUZZLE_TYPE::PILARES_4, "./media/models/level_1/acertijo-hombre-bestia.obj", "./media/textures/acertijo-hombre-bestia.png", {0.0f,3.14f,0.0f});

        // poner un cartel en el puzle diciendo que se tiene que acercar para activar los pilares, carteles de ayuda
    }
}

ECS::Entity &GameObjectFactory::createMessage(float x, float y, float z, float w, float h, float d, const char *message) const
{
    auto &e = m_EntMan.newEntity();

    auto &phy = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &mess = m_EntMan.addComponent<MessageComponent>(e);
    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    body.collider = false;

    phy.position.x = x;
    phy.position.y = y;
    phy.position.z = z;
    phy.layer.AddLayer(LayerRaycast::TRIGGER); // PARA QUE NO LO DETECTE IGUAL

    mess.message = message;
    mess.justUseMessages = true; // para que solo use el cuadro de dialogo

    /* auto& ren = m_EntMan.addComponent<RenderComponent>(e);
    ren.w = w;
    ren.h = h;
    ren.d = d; */

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// TRAPS - TODO
ECS::Entity &GameObjectFactory::createArrowTrap(float x, float y, float z, float w, float h, float d, ECS::EntityType type, ECS::EntityTAG tag) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    e.setTAG(tag);
    auto &phy = m_EntMan.addComponent<PhysicsComponent>(e);

    /* auto& key = createShot(0.0f, -20.0f, 0.0f, 0.15f, 0.15f, 0.15f, ECS::BehaviourState::IDLEB_S, 15, 170);
    auto& key2 = createShot(0.0f, -20.0f, 0.0f, 0.15f, 0.15f, 0.15f, ECS::BehaviourState::IDLEB_S, 15, 170);
    auto& key3 = createShot(0.0f, -20.0f, 0.0f, 0.15f, 0.15f, 0.15f, ECS::BehaviourState::IDLEB_S, 15, 170); */

    phy.position.x = x;
    phy.position.y = y;
    phy.position.z = z;

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// SPAWNER
template <typename CALLABLE_t>
ECS::Entity &GameObjectFactory::createSpawner(float x, float y, float z, [[maybe_unused]] ECS::EntityType type, CALLABLE_t callback) const // de momento lo paso por valor, sino &&callback
{
    auto &e = m_EntMan.newEntity();
    // e.setType(type);
    auto &spw = m_EntMan.addComponent<SpawnerComponent>(e);
    // poinerle el worldCOpmponent para su pos
    auto &phy = m_EntMan.addComponent<PhysicsComponent>(e);

    phy.position.x = x;
    phy.position.y = y;
    phy.position.z = z;
    phy.layer.AddLayer(LayerRaycast::SPAWNER);

    spw.spawnMethod = callback;

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// ASCENSOR
ECS::Entity &GameObjectFactory::createElevator(float x, float y, float z, float w, float h, float d, float distance, bool direction, ECS::SwitchType switchType, ECS::ElevatorDirection sense, std::string fileName, std::string texture) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(ECS::EntityType::ELEVATOR);
    auto &phy = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &ren = m_EntMan.addComponent<RenderComponent>(e);
    auto &ele = m_EntMan.addComponent<ElevatorComponent>(e);
    auto &mess = m_EntMan.addComponent<MessageComponent>(e);
    auto &swit = m_EntMan.addComponent<SwitchComponent>(e);

    ren.node = GE.addSceneModel(fileName, texture, "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z});
    // ren.node = GE.addSceneModel("./media/models/level_1/C_Ascensor.obj", "./media/textures/ascensor-t.png", {0.0f,0.0f,0.0f}, 1, 0, {x, y, z});

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    // body.collider = false;

    // phy.trigger = true;
    phy.kinematic_ = true;
    phy.position.x = x;
    phy.position.y = y;
    phy.position.z = z;
    phy.dimension = {w, h, d};
    phy.restitution = 0.f;
    phy.staticFriction = .85f;
    phy.dynamicFriction = .65f;
    /* phy.staticFriction = .85f;
    phy.dynamicFriction = .65f; */
    phy.mass = 60.f;
    phy.layer.AddLayer(LayerRaycast::ENVIRONMENT);

    ren.w = w;
    ren.h = h;
    ren.d = d;

    ele.distance_toDo = distance;
    ele.working = direction; // false por defecto, ira de arriba a abajo
    ele.direction = sense;
    ele.initial_position = phy.position.y;
    ele.end_position = phy.position.y + distance;
    if (direction)
    {
        ele.initial_position = phy.position.y - distance;
        ele.end_position = phy.position.y;
    }

    mess.justUsePopUpE = true;
    // ya tiene por defecto el usar en la E

    swit.switchType = switchType;

    return e;
}

ECS::Entity &GameObjectFactory::createSwitch(float x, float y, float z, float w, float h, float d, ECS::SwitchType switchType, std::string fileName, std::string texture, glm::vec3 rotation) const
{

    auto &e = m_EntMan.newEntity();
    e.setType(ECS::EntityType::ELEVATOR); // da igual de momento
    auto &phy = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &ren = m_EntMan.addComponent<RenderComponent>(e);
    auto &mess = m_EntMan.addComponent<MessageComponent>(e);
    auto &swit = m_EntMan.addComponent<SwitchComponent>(e);

    ren.node = GE.addSceneModel(fileName, texture, "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z}, rotation);

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    body.collider = false; // sabe que colisiona pero no hay overlap

    phy.static_ = true;
    phy.invMass = 0; // si es estatico tiene que tener esta masa
    phy.position.x = x;
    phy.position.y = y;
    phy.position.z = z;
    phy.dimension = {w, h, d};

    ren.w = w;
    ren.h = h;
    ren.d = d;

    mess.justUsePopUpE = true;
    // ya tiene por defecto el usar en la E

    swit.switchType = switchType;

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// ENTIDADES DEL JUEGO
ECS::Entity &GameObjectFactory::createPlayer(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, [[maybe_unused]] glm::vec3 rotation) const
{
    // PRIMERA ENTIDAD - Jugador
    auto &e = m_EntMan.newEntity();
    // std::cout << "crear player\n";
    e.setType(type);
    e.setTAG(ECS::EntityTAG::E_PLAYER);
    // se piensa que la e no la voy a modificar, por eso da error
    auto &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] auto &cm = m_EntMan.addComponent<CameraComponent>(e); // cambiar esto para que sea una entidad propia
    [[maybe_unused]] auto &bh = m_EntMan.addComponent<ShotBehaviourComponent>(e);
    [[maybe_unused]] auto &cl = m_EntMan.addComponent<ColliderComponent>(e);
    [[maybe_unused]] auto &iv = m_EntMan.addComponent<InventoryComponent>(e);
    auto &per = m_EntMan.addComponent<PerceptionComponent>(e);

    [[maybe_unused]] auto &hc = m_EntMan.addComponent<HealthComponent>(e);
    // hc.health = 74;
    [[maybe_unused]] auto &ic = m_EntMan.addComponent<InputComponent>(e);

    /* [[maybe_unused]] auto &puzzle = m_EntMan.addComponent<PuzzleComponent>(e); */
    [[maybe_unused]] auto &au = m_EntMan.addComponent<AudioComponent>(e);
    [[maybe_unused]] auto &am = m_EntMan.addComponent<AnimationComponent>(e);
    auto &pw = m_EntMan.addComponent<PowerUpComponent>(e);

    // rn.node = GE.addSceneModel("./media/models/Jessica.obj", "./media/textures/texturaJessica.png", {0.78f, 0.56f, 0.78f}, 1, 0, {x, y, z});
    // y = 0.23f;

    // x = -26.6295f;
    // y = 11.003f;
    // z = -70.9486f;
    // rn.node = GE.addSceneSkinModel("./media/animation/Jessica/idle.dae", "./media/textures/texturaJessica.png", 1, 0, {x, y, z}, {0.0f, 0.0f, 0.0f});
    rn.node = GE.addSceneSkinModel("./media/animation/Jessica/idlePistola.dae", "./media/textures/texturaJessica.png", 1, 0, {x, y, z}, {0.0f, 0.0f, 0.0f});

    am.anim = &dynamic_cast<T_AnimationMesh *>(GE.getNode(rn.node)->getEntity<T_AnimationMesh>())->animator_;
    // am.idle = GE.addSceneAnimation("./media/animation/Jessica/idle.dae", "./media/animation/Jessica/idle.dae");
    // am.walk = GE.addSceneAnimation("./media/animation/Jessica/walk.dae", "./media/animation/Jessica/idle.dae");
    // am.crouch = GE.addSceneAnimation("./media/animation/Jessica/downIdle.dae", "./media/animation/Jessica/idle.dae");
    // am.crouchWalk = GE.addSceneAnimation("./media/animation/Jessica/downwalk.dae", "./media/animation/Jessica/idle.dae");
    // am.push = GE.addSceneAnimation("./media/animation/Jessica/push.dae", "./media/animation/Jessica/idle.dae");
    am.idle = GE.addSceneAnimation("./media/animation/Jessica/idlePistola.dae", "./media/animation/Jessica/idlePistola.dae");
    am.walk = GE.addSceneAnimation("./media/animation/Jessica/andarPistola.dae", "./media/animation/Jessica/idlePistola.dae");
    am.crouch = GE.addSceneAnimation("./media/animation/Jessica/IdleagacharsePistola.dae", "./media/animation/Jessica/idlePistola.dae");
    am.crouchWalk = GE.addSceneAnimation("./media/animation/Jessica/andarAgachadoPistola.dae", "./media/animation/Jessica/idlePistola.dae");
    //am.aim = GE.addSceneAnimation("./media/animation/Jessica/idleEscopeta.dae", "./media/animation/Jessica/idlePistola.dae");
    am.push = GE.addSceneAnimation("./media/animation/Jessica/push.dae", "./media/animation/Jessica/idlePistola.dae");
    // am.animationList.insert(std::make_pair("idle", GE.addSceneAnimation("./media/animation/Jessica/downwalk.dae", "./media/animation/Jessica/downwalk.dae")));
    am.anim->setAnimation(am.idle);

    // rn.emisor = GE.addSceneParticleEmiter({0.94f,0.68f,0.4f}, rn.node, 0, {x,0.5f,z}, {0.0f,0.0f,0.0f}, {0.1f,0.1f,0.1f});
    // auto affector = std::make_unique<AffectorDirection>(glm::vec3{0.0f,0.0f,1.0f}, 0.09f);
    // GE.getNode(rn.emisor)->getEntity<T_EParticleEmiter>()->pushAffector(std::move(affector));

    w = 1.0f;
    h = 2.0f;
    d = 1.0f;

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d; /* ph.mass = 50; */

    // no tiene ningun arma, esta vez hasta que dispare
    bh.type = ECS::BehaviourType::Pistol;
    bh.shot_ammo = 8;

    // ph.use_gravity = false;
    ph.dynamic_ = true;
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.mass = 75.f;
    ph.invMass = 1.f / ph.mass;
    ph.dimension = {w, h, d};
    ph.restitution = 0.1f; // que no haya rebote contra el
    ph.staticFriction = 1.f;
    ph.dynamicFriction = 1.f;
    ph.hasImpulse = false; // para que no reaccione con lo demas rebotando
    ph.maxForceSprint = 8000.f;
    ph.layer.AddLayer(LayerRaycast::PLAYER);

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.player_bend = h / 2.f;
    rn.player_noBend = h;
    rn.color = c;
    rn.damaged_color_reset = c;

    // como devuelvo a el mismo, puedo seguir añadiendo datos
    au.AddAudioInstance("GUN", audio.createInstance("GUN", "Efectos/gun_shot"))
        .AddAudioInstance("WALKING", audio.createInstance("WALKING", "Efectos/steps_echo"))
        .AddAudioInstance("HURT", audio.createInstance("HURT_JESS", "Voces/jess_hurt"))
        .AddAudioInstance("RELOAD_JESS", audio.createInstance("RELOAD_JESS", "Efectos/reload"))
        .AddAudioInstance("HEAL1_JESS", audio.createInstance("HEAL1_JESS", "Efectos/heal1"))
        .AddAudioInstance("HEAL2_JESS", audio.createInstance("HEAL2_JESS", "Efectos/heal2"))
        .AddAudioInstance("DIE_JESS", audio.createInstance("DIE_JESS", "Voces/jess_die"));

    audio.getInstances("WALKING")[0]->SetVolume(0.25f);

    // raycast - no lo necesita
    per.useRaycast = false;
    /* per.raycast.layer.AddLayer() */
    /* pc.origin = ph.position;
    pc.range = 3.f; */
    // ry.direction = {1.f,0.f,0.f}; // ver la primera direccion que toma el playerForward

    // audio range
    per.addRadioSound("GUN", 6)
        .addRadioSound("WALKING", 1)
        .addRadioSound("HURT_JESS", 1)
        .addRadioSound("RELOAD_JESS", 2)
        .addRadioSound("DIE_JESS", 2); // añadir mas sonidos

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// se crea con comportamiento de destruccion porque solo existira por breve tiempo
ECS::Entity &GameObjectFactory::createShot(float x, float y, float z, float w, float h, float d, ECS::BehaviourState state, int16_t shot_damage, uint32_t distance_toDo, glm::vec3 direction) const
{
    // ENTIDAD - Bala
    auto &e_bala = m_EntMan.newEntity();

    e_bala.setType(ECS::EntityType::BULLET);
    e_bala.setState(ECS::EntityState::MOVING_FORWARDS);
    auto &ph_bala = m_EntMan.addComponent<PhysicsComponent>(e_bala);
    auto &rn_bala = m_EntMan.addComponent<RenderComponent>(e_bala);
    auto &be_bala = m_EntMan.addComponent<ShotBehaviourComponent>(e_bala);
    [[maybe_unused]] auto &cl_bala = m_EntMan.addComponent<ColliderComponent>(e_bala);

    rn_bala.node = -1;
    rn_bala.movableModel = false;

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e_bala);
    body.bBox_.xMax = w + 1.5f;
    body.bBox_.yMax = h + 2.f;
    body.bBox_.zMax = d + 1.5f;
    body.collider = false;

    // pasarle el otro destroy
    be_bala.state = state;
    be_bala.initial_count = distance_toDo;
    be_bala.counter = be_bala.initial_count;
    be_bala.shot_damage = shot_damage;

    ph_bala.kinematic_ = true;
    ph_bala.position.x = x;
    ph_bala.position.y = y;
    ph_bala.position.z = z;
    ph_bala.forceDirection = direction;
    ph_bala.maxForceSprint = FLT_MAX;
    ph_bala.layer.AddLayer(LayerRaycast::ENVIRONMENT);
    // ponerlo por fuezas

    // quitar si se le pone modelo a la bala la suma
    rn_bala.w = w + 1.5f;
    rn_bala.h = h + 2.f;
    rn_bala.d = h + 1.5f;
    rn_bala.color = {0.0f, 0.0f, 0.0f};

    return e_bala;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createEnemyArrow(float x, float z, float tx, float tz, glm::vec3 c)
{
    // std::cout << "*** CREAR FLECHA at" << x << ", " << z << " con target " << tx << ", " << tz << std::endl;
    auto &e = m_EntMan.newEntity();
    e.setState(ECS::EntityState::MOVING_IA);
    e.setType(ECS::EntityType::PROJECTILE);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);
    ShotBehaviourComponent &be = m_EntMan.addComponent<ShotBehaviourComponent>(e);

    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = 1.0f;
    body.bBox_.yMax = 2.6f;
    body.bBox_.zMax = 1.0f;

    be.state = ECS::BehaviourState::DestroyP;
    be.initial_count = 90;
    be.shot_damage = 15;

    float separacion = 1.0f;

    if (x < tx)
    {
        x += separacion;
    }
    else
    {
        x -= separacion;
    }

    if (z < tz)
    {
        z += separacion;
    }
    else
    {
        z -= separacion;
    }

    if (tx < x && tx > 0)
    {
        tx *= -1;
    }
    if (tz < z && tz > 0)
    {
        tz *= -1;
    }
    if (tx > x && tx < 0)
    {
        tx *= -1;
    }
    if (tz > z && tz < 0)
    {
        tz *= -1;
    }

    ph.use_gravity = false;
    ph.dynamic_ = true;
    ph.position.x = x;
    ph.position.y = escarabajoY;
    ph.position.z = z;

    ph.ownForces.x = tx / 100;
    ph.ownForces.z = tz / 100;
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);

    rn.w = 0.6f;
    rn.h = 0.6f;
    rn.d = 0.6f;
    rn.color = c;
    rn.damaged_color_reset = c;

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createEnemyEscarabajo(float x, float z, glm::vec3 c, SB sbt, BehaviourTree *behavTree, float pt)
{
    auto &e = m_EntMan.newEntity();
    e.setState(ECS::EntityState::MOVING_IA);
    e.setType(ECS::EntityType::ENEMY);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);
    [[maybe_unused]] AIComponent &ai = m_EntMan.addComponent<AIComponent>(e);
    [[maybe_unused]] HealthComponent &hc = m_EntMan.addComponent<HealthComponent>(e);
    [[maybe_unused]] PathComponent &pc = m_EntMan.addComponent<PathComponent>(e);
    [[maybe_unused]] auto &am = m_EntMan.addComponent<AnimationComponent>(e);
    auto &per = m_EntMan.addComponent<PerceptionComponent>(e);
    [[maybe_unused]] auto &au = m_EntMan.addComponent<AudioComponent>(e);

    rn.node = GE.addSceneModel("./media/models/level_1/escarabajo.obj", "./media/textures/escarabajo-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, 0.f, z}, {0.0f, 0.0f, 0.0f});

    // body
    

    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = 1.2f;
    body.bBox_.yMax = 2.6f;
    body.bBox_.zMax = 1.2f;

    behavTree->clearNodes();
    ai.behaviourTree = nullptr;
    behavTree->initTreeZombie(); // de momento es el mismo
    ai.behaviourTree = behavTree;

    ai.behaviour = sbt;
    ai.enemyType = 2;
    ai.perceptionTime = pt;
    ai.idleRangeMaxx = x + ECS::aiIdleRange;
    ai.idleRangeMinx = x - ECS::aiIdleRange;
    ai.idleRangeMaxz = z + ECS::aiIdleRange;
    ai.idleRangeMinz = z - ECS::aiIdleRange;
    ai.damage = 5.0f;
    ai.arrivalRadius = 1.0f;

    // ph.kinematic_ = true; // seguira un recorrido en el aire predefinido
    ph.use_gravity = false;
    ph.dynamic_ = true;
    /*     ph.x = x;
        ph.y = escarabajoY;
        ph.z = z; */
    ph.position.x = x;
    ph.position.y = escarabajoY;
    ph.position.z = z;
    ph.layer.AddLayer(LayerRaycast::ENEMY);
    // ph.acelerationZ = 0.2f;
    // ph.acelerationX = 0.2f;
    // ph.velZ = 0.f;
    // ph.velX = 0.f;

    per.hasSigth = true;
    per.raycast.origin = ph.position;
    per.raycast.range = 15.5f;
    per.raycast.direction = GE.getNode(rn.node)->getModelDirection();
    /* std::cout << per.raycast.direction.x << " , " << per.raycast.direction.z << "\n";  */
    per.raycast.direction.y = 0.f;
    per.layersToDetect.AddLayer(LayerRaycast::PLAYER); // entiddes que quiero percibir
    // layers para detectar el raycast solo
    per.raycast.layer.AddLayer(LayerRaycast::PLAYER);
    per.raycast.layer.AddLayer(LayerRaycast::ENVIRONMENT);
    /* per.raycast.layer.AddLayer(LayerRaycast::ENEMY); */

    // per.hasHearing = true;

    rn.w = 0.6f;
    rn.h = 0.6f;
    rn.d = 0.6f;
    rn.color = c;
    rn.damaged_color_reset = c;
    // ai.patrol = {
    //     ECS::Vector3{ph.x + 0.f, ph.y, ph.z + 10.f},
    //     {ph.x + 0.f, ph.y, ph.z + 0.f}};

    hc.health = 20;
    hc.hasInmunity = false;

    au.AddAudioInstance("FLY_BEETLE", audio.createInstance("FLY_BEETLE", "Voces/beetle_fly"))
        .AddAudioInstance("HURT", audio.createInstance("HURT_BEETLE", "Voces/beetle_hurt"))
        .AddAudioInstance("DIE", audio.createInstance("HISS_BEETLE", "Voces/beetle_hiss"));
    return e;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createEnemyZombie(float x, float y, float z, glm::vec3 rotation, SB sbt, BehaviourTree *behavTree, float pt)
{
    auto &e = m_EntMan.newEntity();
    e.setState(ECS::EntityState::MOVING_IA);
    e.setType(ECS::EntityType::ENEMY);
    e.setTAG(ECS::EntityTAG::ENEMY_Z1);
    auto &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] auto &cl = m_EntMan.addComponent<ColliderComponent>(e);
    [[maybe_unused]] auto &ai = m_EntMan.addComponent<AIComponent>(e);
    [[maybe_unused]] auto &pc = m_EntMan.addComponent<PathComponent>(e);
    [[maybe_unused]] auto &hc = m_EntMan.addComponent<HealthComponent>(e);
    [[maybe_unused]] auto &per = m_EntMan.addComponent<PerceptionComponent>(e);
    [[maybe_unused]] auto &au = m_EntMan.addComponent<AudioComponent>(e);
    [[maybe_unused]] auto &am = m_EntMan.addComponent<AnimationComponent>(e);

    hc.health = 50;
    hc.hasInmunity = false; // los enemigos las veces que les dispares les haces daño

    rn.node = GE.addSceneSkinModel("./media/animation/Infectado/Infectadoidle.dae", "./media/textures/TexturaInfectadp.png", 1, 0, {x, y, z}, {0.0f, 0.5f, 0.0f});
    // rn.node = GE.addSceneModel("./media/models/Z_Zombie.obj", "./media/textures/TexturaInfectado.png", {1.0f, 0.0f, 0.0f}, 1, 0, {x, y, z});

    // Animaciones
    am.anim = &dynamic_cast<T_AnimationMesh *>(GE.getNode(rn.node)->getEntity<T_AnimationMesh>())->animator_;
    am.idle = GE.addSceneAnimation("./media/animation/Infectado/Infectadoidle.dae", "./media/animation/Infectado/Infectadoidle.dae");
    am.walk = GE.addSceneAnimation("./media/animation/Infectado/Infectadowalk.dae", "./media/animation/Infectado/Infectadoidle.dae");
    //am.attack = GE.addSceneAnimation("./media/animation/Infectado/attack.dae", "./media/animation/Jessica/Infectadoidle.dae");
    am.anim->setAnimation(am.idle);

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = 1.f;
    body.bBox_.yMax = 2.f;
    body.bBox_.zMax = 1.f;

    behavTree->clearNodes();
    ai.behaviourTree = nullptr;
    behavTree->initTreeZombie();
    ai.behaviourTree = behavTree;

    // std::cout << "enemy behav: " << sbt << std::endl;

    ai.behaviour = sbt;
    // std::cout << "ASSIGNED enemy behav: " << ai.behaviour << std::endl;
    ai.enemyType = 1;
    ai.perceptionTime = pt;
    ai.idleRangeMaxx = x + ECS::aiIdleRange;
    ai.idleRangeMinx = x - ECS::aiIdleRange;
    ai.idleRangeMaxz = z + ECS::aiIdleRange;
    ai.idleRangeMinz = z - ECS::aiIdleRange;
    ai.damage = 15.0f;
    ai.arrivalRadius = 1.5f;

    // cambair a fuerzas
    ph.dynamic_ = true;
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {1.f, 2.f, 1.f};
    ph.layer.AddLayer(LayerRaycast::ENEMY);

    rn.w = 1.f;
    rn.h = 2.f;
    rn.d = 1.f;
    /* rn.color = c; */

    // raycast
    per.hasSigth = true;
    per.raycast.origin = ph.position;
    per.raycast.range = 15.5f;
    per.raycast.direction = GE.getNode(rn.node)->getModelDirection();
    /* std::cout << per.raycast.direction.x << " , " << per.raycast.direction.z << "\n";  */
    per.raycast.direction.y = 0.f;
    per.layersToDetect.AddLayer(LayerRaycast::PLAYER); // entiddes que quiero percibir
    // layers para detectar el raycast solo
    per.raycast.layer.AddLayer(LayerRaycast::PLAYER);
    per.raycast.layer.AddLayer(LayerRaycast::ENVIRONMENT);
    per.raycast.layer.AddLayer(LayerRaycast::ENEMY);

    per.hasHearing = true; // solo poner true si puede escuchar, pero no emitira ningun sonido

    au.AddAudioInstance("HURT", audio.createInstance("HURT_ZOMBIE", "Voces/infected_hurt"))
        .AddAudioInstance("AGRO_ZOMBIE", audio.createInstance("AGRO_ZOMBIE", "Voces/infected_agro"))
        .AddAudioInstance("DIE", audio.createInstance("DIE_ZOMBIE", "Voces/infected_die"))
        .AddAudioInstance("STEPS_ZOMBIE", audio.createInstance("STEPS_ZOMBIE", "Efectos/steps_infected"));
    // rn.damaged_color_reset = c;
    // ai.patrol = {
    //     ECS::Vector3{ph.x + 0.f, ph.y, ph.z + 10.f},
    //     {ph.x + 0.f, ph.y, ph.z + 0.f}};

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createEnemyMomia(float x, float y, float z, glm::vec3 c, SB sbt, BehaviourTree *behavTree, float pt)
{
    auto &e = m_EntMan.newEntity();
    e.setState(ECS::EntityState::MOVING_IA);
    e.setType(ECS::EntityType::ENEMY);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);
    AIComponent &ai = m_EntMan.addComponent<AIComponent>(e);
    [[maybe_unused]] PathComponent &pc = m_EntMan.addComponent<PathComponent>(e);
    [[maybe_unused]] HealthComponent &hc = m_EntMan.addComponent<HealthComponent>(e);
    [[maybe_unused]] PerceptionComponent &per = m_EntMan.addComponent<PerceptionComponent>(e);
    [[maybe_unused]] auto &am = m_EntMan.addComponent<AnimationComponent>(e);
    ShotBehaviourComponent &bh = m_EntMan.addComponent<ShotBehaviourComponent>(e);
    [[maybe_unused]] auto &au = m_EntMan.addComponent<AudioComponent>(e);

    hc.health = 70;

    //rn.node = GE.addSceneModel("./media/models/Z_Zombie.obj", "./media/textures/TexturaInfectado.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z});
    rn.node = GE.addSceneSkinModel("./media/animation/Momia/momiaIdle.dae", "./media/textures/momia.png", 1, 0, {x, y, z}, {0.0f, 0.5f, 0.0f});
    // body
    am.anim = &dynamic_cast<T_AnimationMesh *>(GE.getNode(rn.node)->getEntity<T_AnimationMesh>())->animator_;
    am.idle = GE.addSceneAnimation("./media/animation/Momia/momiaIdle.dae", "./media/animation/Momia/momiaIdle.dae");
    am.walk = GE.addSceneAnimation("./media/animation/Momia/momiaWalk.dae", "./media/animation/Momia/momiaIdle.dae");
    // // // am.attack = GE.addSceneAnimation("./media/animation/Infectado/downIdle.dae", "./media/animation/Jessica/idle.dae");
    am.anim->setAnimation(am.idle);

    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = 1.f;
    body.bBox_.yMax = 2.f;
    body.bBox_.zMax = 1.f;

    behavTree->clearNodes();
    ai.behaviourTree = nullptr;
    behavTree->initTreeMomia();
    ai.behaviourTree = behavTree;

    bh.type = ECS::BehaviourType::Pistol;
    bh.shot_ammo = 8;

    // std::cout << "enemy behav: " << sbt << std::endl;

    ai.behaviour = sbt;
    // std::cout << "ASSIGNED enemy behav: " << ai.behaviour << std::endl;
    ai.enemyType = 3;
    ai.perceptionTime = pt;
    ai.idleRangeMaxx = x + ECS::aiIdleRange;
    ai.idleRangeMinx = x - ECS::aiIdleRange;
    ai.idleRangeMaxz = z + ECS::aiIdleRange;
    ai.idleRangeMinz = z - ECS::aiIdleRange;
    ai.damage = 20.0f;
    ai.arrivalRadius = 1.f;

    // cambair a fuerzas
    ph.dynamic_ = true;
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {1.f, 2.f, 1.f};
    ph.layer.AddLayer(LayerRaycast::ENEMY);

    rn.w = 1.f;
    rn.h = 2.f;
    rn.d = 1.f;
    rn.color = c;

    // raycast
    per.hasSigth = true;
    per.raycast.origin = ph.position;
    per.raycast.range = 15.f;
    per.raycast.direction = GE.getNode(rn.node)->getModelDirection();
    per.raycast.direction.y = 0.f;

    per.hasHearing = true;

    au.AddAudioInstance("HURT", audio.createInstance("HURT_MUMMY", "Voces/mummy_hurt"))
        .AddAudioInstance("DIE", audio.createInstance("DIE_MUMMY", "Voces/mummy_die"))
        .AddAudioInstance("STEPS_MUMMY", audio.createInstance("STEPS_MUMMY", "Efectos/steps_mummy"));
    return e;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createEnemyMomiaLaberinto(float x, float y, float z, glm::vec3 c, SB sbt, BehaviourTree *behavTree, float pt)
{
    auto &e = m_EntMan.newEntity();
    e.setState(ECS::EntityState::MOVING_IA);
    e.setType(ECS::EntityType::ENEMY);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);
    AIComponent &ai = m_EntMan.addComponent<AIComponent>(e);
    [[maybe_unused]] PathComponent &pc = m_EntMan.addComponent<PathComponent>(e);
    [[maybe_unused]] HealthComponent &hc = m_EntMan.addComponent<HealthComponent>(e);
    [[maybe_unused]] PerceptionComponent &per = m_EntMan.addComponent<PerceptionComponent>(e);
    [[maybe_unused]] auto &am = m_EntMan.addComponent<AnimationComponent>(e);
    // ShotBehaviourComponent &bh = m_EntMan.addComponent<ShotBehaviourComponent>(e);
    [[maybe_unused]] auto &au = m_EntMan.addComponent<AudioComponent>(e);

    hc.health = 70;
    hc.hasInmunity = false;

    // rn.node = GE.addSceneModel("./media/models/Z_Zombie.obj", "./media/textures/TexturaInfectado.png", "./media/models/vida.mtl", {0.923f,0.729f,0.239f}, {0.0f,1.5f,-1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z});
    rn.node = GE.addSceneSkinModel("./media/animation/Momia/momiaIdle.dae", "./media/textures/momia.png", 1, 0, {x, y, z}, {0.0f, 3.1415927410125732f, 0.0f});
    // rn.node = GE.addSceneModel("./media/models/Z_Zombie.obj", "./media/textures/TexturaInfectado.png", {1.0f, 0.0f, 0.0f}, 1, 0, {x, y, z});

    // Animaciones
    am.anim = &dynamic_cast<T_AnimationMesh *>(GE.getNode(rn.node)->getEntity<T_AnimationMesh>())->animator_;
    am.idle = GE.addSceneAnimation("./media/animation/Momia/momiaIdle.dae", "./media/animation/Momia/momiaIdle.dae");
    am.walk = GE.addSceneAnimation("./media/animation/Momia/momiaWalk.dae", "./media/animation/Momia/momiaIdle.dae");
    // // // am.attack = GE.addSceneAnimation("./media/animation/Infectado/downIdle.dae", "./media/animation/Jessica/idle.dae");
    am.anim->setAnimation(am.idle);

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = 1.f;
    body.bBox_.yMax = 2.f;
    body.bBox_.zMax = 1.f;

    behavTree->clearNodes();
    ai.behaviourTree = nullptr;
    behavTree->initTreeMomiaLaberinto();
    ai.behaviourTree = behavTree;

    // bh.type = ECS::BehaviourType::Pistol;
    // bh.shot_ammo = 8;

    // std::cout << "enemy behav: " << sbt << std::endl;

    ai.behaviour = sbt;
    // std::cout << "ASSIGNED enemy behav: " << ai.behaviour << std::endl;
    ai.enemyType = 4;
    ai.perceptionTime = pt;
    ai.idleRangeMaxx = x + ECS::aiIdleRange;
    ai.idleRangeMinx = x - ECS::aiIdleRange;
    ai.idleRangeMaxz = z + ECS::aiIdleRange;
    ai.idleRangeMinz = z - ECS::aiIdleRange;
    ai.damage = 50.0f; // si te pega una vez te mata
    ai.arrivalRadius = 1.f;

    // cambair a fuerzas
    ph.dynamic_ = true;
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {1.f, 2.f, 1.f};
    ph.layer.AddLayer(LayerRaycast::ENEMY);

    rn.w = 1.f;
    rn.h = 2.f;
    rn.d = 1.f;
    rn.color = c;

    // rn.damaged_color_reset = c;
    // ai.patrol = {
    //     ECS::Vector3{ph.x + 0.f, ph.y, ph.z + 10.f},
    //     {ph.x + 0.f, ph.y, ph.z + 0.f}};

    // raycast
    per.hasSigth = true;
    per.raycast.origin = ph.position;
    per.raycast.range = 15.f;
    per.raycast.direction = GE.getNode(rn.node)->getModelDirection();
    per.raycast.direction.y = 0.f;

    per.hasHearing = true;

    au.AddAudioInstance("HURT", audio.createInstance("HURT_MUMMY", "Voces/mummy_hurt"))
        .AddAudioInstance("DIE", audio.createInstance("DIE_MUMMY", "Voces/mummy_die"))
        .AddAudioInstance("STEPS_MUMMY", audio.createInstance("STEPS_MUMMY", "Efectos/steps_mummy"));

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// poner para pasarles el tipo de entidad que quiero que cree
ECS::Entity &GameObjectFactory::createObject(/* bool spawn,  */ float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, std::string fileName, std::string texture, [[maybe_unused]] glm::vec3 rotation, ECS::EntityTAG tag) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    e.setTAG(tag);
    auto &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &rn = m_EntMan.addComponent<RenderComponent>(e);
    auto &ms = m_EntMan.addComponent<MessageComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);

    rn.node = GE.addSceneModel(fileName, texture, "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z}, rotation);
    rn.movableModel = false;
    // rn.node = GE.addSceneModel("./media/models/A_Municion.obj", "./media/textures/municion-t.png", {1.0f, 0.0f, 0.0f}, 1, 0, {x, y, z});

    /* GE.addSceneBillboard("./media/img/F.png", 1, 0, {x, y, z}); */

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    body.collider = false;

    ph.static_ = true;
    ph.invMass = 0; // si es estatico tiene que tener esta masa
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {w, h, d};
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = c;
    rn.damaged_color_reset = c;

    ms.justUsePopUpE = true;
    ms.messageUse = "PRESS F";

    return e;
}

ECS::Entity &GameObjectFactory::createObjectEOL(float x, float y, float z, float w, float h, float d, ECS::EntityType type, [[maybe_unused]] glm::vec3 rotation) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    auto &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &rn = m_EntMan.addComponent<RenderComponent>(e);

    rn.node = GE.addSceneModel("./media/models/Y_Final.obj", "./media/models/Y_Final.mtl", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z});
    rn.movableModel = false;

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    body.collider = false;

    ph.static_ = true;
    ph.invMass = 0; // si es estatico tiene que tener esta masa
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {w, h, d};
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);

    rn.w = w;
    rn.h = h;
    rn.d = d;

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createObject4movement(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, [[maybe_unused]] glm::vec3 rotation, float mass) const
{
    auto &e = m_EntMan.newEntity();
    e.setState(ECS::EntityState::MOVING_BOX);
    e.setType(type);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);

    rn.node = GE.addSceneModel("./media/models/caja1.obj", "./media/textures/caja1-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z});

    w = 2.3f;
    h = 2.5f;
    d = 2.3f;

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;

    // ph.use_gravity = false;
    ph.dynamic_ = true; // objeto que se podra mover
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.mass = mass;
    ph.invMass = 1.f / ph.mass;
    ph.dimension = {w, h, d};
    ph.restitution = 0.f;
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);
    ph.staticFriction = 0.f;
    ph.dynamicFriction = 0.f;

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = c;
    rn.damaged_color_reset = c;

    // añadir sonidos

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createKey(/* bool spawn,  */ float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, glm::vec3 rotation, std::string fileName, std::string texture, ECS::EntityTAG tag) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    e.setTAG(tag);
    auto &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &rn = m_EntMan.addComponent<RenderComponent>(e);
    /* auto &dr = m_EntMan.addComponent<DoorComponent>(e); */
    auto &ms = m_EntMan.addComponent<MessageComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);

    rn.node = GE.addSceneModel(fileName, texture, "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z});
    rn.movableModel = false;

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    body.collider = false;

    ph.static_ = true;
    ph.invMass = 0; // si es estatico tiene que tener esta masa
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {w, h, d};
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = c;
    rn.damaged_color_reset = c;

    ms.justUsePopUpE = true;
    ms.messageUse = "PULSA F*";

    /* if(type == ECS::EntityType::KEY){
        dr.keyType = keyType;
    } */

    return e;
}

// //////////////////////////////////////////////////////////////else if (values[0].compare("B") == 0)
//     cr//////////////
ECS::Entity &GameObjectFactory::createDoor(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityTAG keyTag, ECS::EntityType doorType, glm::vec3 rotation) const
{
    auto &e_door = m_EntMan.newEntity();
    e_door.setType(doorType);
    auto &ph = m_EntMan.addComponent<PhysicsComponent>(e_door);
    auto &rn = m_EntMan.addComponent<RenderComponent>(e_door);
    /* [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e_door); */
    auto &mess = m_EntMan.addComponent<MessageComponent>(e_door);
    auto &audi = m_EntMan.addComponent<AudioComponent>(e_door);
    [[maybe_unused]] auto &dr = m_EntMan.addComponent<DoorComponent>(e_door);

    rn.node = GE.addSceneModel("./media/models/puerta.obj", "./media/textures/puerta-t.png", "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z}, rotation);
    rn.movableModel = false;

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e_door);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;

    ph.static_ = true;
    ph.invMass = 0; // si es estatico tiene que tener esta masa
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {w, h, d};
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = c;

    dr.doorType = doorType;
    dr.keyTag = keyTag;

    mess.justUsePopUpE = true;

    /* audi.AddAudioInstance("DOOR_OPEN", audio.getInstances("DOOR_OPEN").at(0))
    .AddAudioInstance("DOOR_CLOSED", audio.getInstances("DOOR_CLOSED").at(0)); */

    audi.AddAudioInstance("DOOR_OPEN", audio.createInstance("DOOR_OPEN", "Efectos/door_open"))
        .AddAudioInstance("DOOR_CLOSED", audio.createInstance("DOOR_CLOSED", "Efectos/door_closed"));

    return e_door;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createObject4Objective(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, [[maybe_unused]] glm::vec3 rotation) const
{
    auto &e_4objective = m_EntMan.newEntity();
    e_4objective.setType(type);
    auto &ph = m_EntMan.addComponent<PhysicsComponent>(e_4objective);
    auto &rn = m_EntMan.addComponent<RenderComponent>(e_4objective);
    /* [[maybe_unused]] auto &cl = m_EntMan.addComponent<ColliderComponent>(e_4objective); */
    auto &mess = m_EntMan.addComponent<MessageComponent>(e_4objective);

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e_4objective);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;

    ph.static_ = true;
    ph.invMass = 0; // si es estatico tiene que tener esta masa
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {w, h, d};
    ph.staticFriction = .85f;
    ph.dynamicFriction = .65f;
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = c;

    mess.justUsePopUpE = true;

    // añadir sonidos

    return e_4objective;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createFloor(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, [[maybe_unused]] glm::vec3 rotation) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);
    // std::cout << "id E2: " << e2.getId() << std::endl;

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;

    ph.static_ = true;
    ph.invMass = 0.f; // si es estatico tiene que tener este valor a 0
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {w, h, d};
    ph.restitution = 0.f;
    ph.staticFriction = .85f;
    ph.dynamicFriction = .65f;
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);
    /* ph.mass = 65.f; */

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = c;

    return e;
}

//////////////////////////////////////////
ECS::Entity &GameObjectFactory::createSpawnFloor(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, std::string fileName, std::string texture, [[maybe_unused]] glm::vec3 rotation) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);
    // std::cout << "id E2: " << e2.getId() << std::endl;

    rn.node = GE.addSceneModel(fileName, texture, "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z});
    rn.movableModel = false;

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;

    ph.static_ = true;
    ph.invMass = 0.f; // si es estatico tiene que tener este valor a 0
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {w, h, d};
    ph.restitution = .25f;
    ph.staticFriction = .85f;
    ph.dynamicFriction = .65f;
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);
    /* ph.mass = 65.f; */

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = c;

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createWall(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, [[maybe_unused]] glm::vec3 rotation) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    auto &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    auto &rn = m_EntMan.addComponent<RenderComponent>(e);

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    // body.collider = false;*/

    ph.static_ = true;
    ph.invMass = 0; // si es estatico tiene que tener esta masa
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {w, h, d};
    ph.restitution = 0.0f;
    ph.staticFriction = 0.10f;
    ph.dynamicFriction = 0.05f;
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = c;

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
ECS::Entity &GameObjectFactory::createRoof(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, [[maybe_unused]] glm::vec3 rotation) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    // body.collider = false;

    ph.static_ = true;
    ph.invMass = 0; // si es estatico tiene que tener esta masa
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.restitution = .0f;
    ph.staticFriction = .85f;
    ph.dynamicFriction = .65f;
    ph.layer.AddLayer(LayerRaycast::ENVIRONMENT);

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = c;

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// CAMARA
ECS::Entity &GameObjectFactory::createCamera(int idCam, float xPos, float yPos, float zPos, float xTar, float yTar, float zTar,
                                             float xBox, float yBox, float zBox, float w, float h, float d, glm::vec3 color, int orientation, float fovy, ECS::EntityType type, ECS::EntityTAG tag) const
{
    auto &e = m_EntMan.newEntity();
    e.setType(type);
    e.setTAG(tag);
    CameraComponent &ca = m_EntMan.addComponent<CameraComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);

    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    body.collider = false;

    ph.camare_ = true;
    ph.position.x = xBox;
    ph.position.y = yBox;
    ph.position.z = zBox;
    ph.dimension = {w, h, d};
    ph.layer.AddLayer(LayerRaycast::CAMERA);
    /*     ph.restitution = .0f;
        ph.staticFriction = .85f;
        ph.dynamicFriction = .65f;
        ph.velocity = {2.f, 2.f, 2.f};
        ph.mass = 60.f; */

    ca.idCam = idCam;
    ca.cameraPosition.x = xPos;
    ca.cameraPosition.y = yPos;
    ca.cameraPosition.z = zPos;
    ca.cameraTarget.x = xTar;
    ca.cameraTarget.y = yTar;
    ca.cameraTarget.z = zTar;
    ca.cameraFovy = fovy;

    ca.orientation = orientation;

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = color;

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// TRIGGERS
ECS::Entity &GameObjectFactory::createTrigger(float x, float y, float z, float w, float h, float d, ECS::EntityType type, std::string fileName, std::string texture, [[maybe_unused]] glm::vec3 rotation,  ECS::EntityTAG tag) const
{

    auto &e = m_EntMan.newEntity();
    e.setType(type);
    e.setTAG(tag);
    PhysicsComponent &ph = m_EntMan.addComponent<PhysicsComponent>(e);
    RenderComponent &rn = m_EntMan.addComponent<RenderComponent>(e);
    [[maybe_unused]] ColliderComponent &cl = m_EntMan.addComponent<ColliderComponent>(e);

    rn.node = GE.addSceneModel(fileName, texture, "./media/models/vida.mtl", {0.923f, 0.729f, 0.239f}, {0.0f, 1.5f, -1.0f}, 0.9f, 0.3f, 0.6f, 1, 0, {x, y, z});
    // body
    auto &body = m_EntMan.addComponent<bodyComponent>(e);
    body.bBox_.xMax = w;
    body.bBox_.yMax = h;
    body.bBox_.zMax = d;
    // body.collider = false;

    ph.trigger = true;
    ph.position.x = x;
    ph.position.y = y;
    ph.position.z = z;
    ph.dimension = {w, h, d};
    ph.layer.AddLayer(LayerRaycast::TRIGGER);

    rn.w = w;
    rn.h = h;
    rn.d = d;
    rn.color = {0.0f, 0.0f, 0.0f};

    return e;
}

// ////////////////////////////////////////////////////////////////////////////
// CARGA DE MAPA
uint64_t GameObjectFactory::loadModelsDataFromTxt(std::string filePath, [[maybe_unused]] glm::vec3 color)
{
    // ////////////////////////////////////////////////////////////
    // Crga del mapa
    std::ifstream file(filePath.data());
    std::string values[11];

    if (!file)
        throw std::runtime_error("Problema al abrir el TXT\n");
    std::string texto;
    uint64_t totalElements{0};
    int contZ = -1;
    while (getline(file, texto))
    {
        std::string delimiter = ",";

        size_t pos = 0, cont = 0;
        std::string token;
        while ((pos = texto.find(delimiter)) != std::string::npos)
        {
            token = texto.substr(0, pos);
            values[cont] = token;
            // values[cont] = std::stof(token);
            if (cont == 10)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.01, 0.04);
                double ptime = dis(gen);

                if (values[0].compare("J") == 0)
                {
                    // std::cout << values[0] << " : " << std::stof(values[1]) << " : " << std::stof(values[3]) << " : " << std::stof(values[2]) << " : " << std::stof(values[4]) << " : " << std::stof(values[6]) << " : " << std::stof(values[5]) << std::endl;
                    createPlayer(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::PLAYER, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                }
                else if (values[0].compare("S") == 0)
                    createFloor(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::SUELO, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                else if (values[0].compare("P") == 0)
                    createWall(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::PARED, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                else if (values[0].compare("M") == 0)
                    createFloor(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::SUELO_MUERTE, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                else if (values[0].compare("B") == 0)
                    createObject4movement(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::BOX, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])}, 125.f);
                else if (values[0].compare("T") == 0)
                    createWall(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::PARED, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                // else if (values[0].compare("A") == 0)
                // createObject(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::AMMO, "./media/models/A_Municion.obj", "./media/textures/municion-t.png", {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                // else if (values[0].compare("C") == 0)
                //     createObject4Objective(std::stof(values[1]), std::stof(values[3]) + 1, std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::PILAR, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                // // else if (values[0].compare("E") == 0)
                //     createObject4Puzzle(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::PUZZLE_TYPE::PILARES, ECS::PUZZLE_TYPE::PILARES_1, "./media/models/E_Estatua.obj", "./media/textures/municion-t.png");
                // else if (values[0].compare("L") == 0)
                // createKey(std::stof(values[1]), std::stof(values[3]) + 1, std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, static_cast<ECS::EntityType>(std::stof(values[7])), {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])}, "./media/models/L_Llave.obj", "./media/textures/llave.png"); // VA CON EL MISMO valor de la llave
                // else if (values[0].compare("D") == 0)
                // createDoor(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, static_cast<ECS::EntityType>(std::stof(values[7])), ECS::EntityType::DOOR_KEY, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])}); // VA CON EL MISMO valor de la llave
                // else if (values[0].compare("N") == 0)
                // createDoor(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::DOOR_NO_KEY, ECS::EntityType::DOOR_NO_KEY, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])}); // VA SIN LLAVE
                // else if (values[0].compare("V") == 0)
                // createObject(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::BIG_HEAL, "./media/models/curaG.obj", "./media/textures/curaG-t.png", {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                // else if (values[0].compare("H") == 0)
                // createObject(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::SMALL_HEAL, "./media/models/H_pastillas.obj", "./media/textures/patillas-t.png", {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                else if (values[0].compare("F") == 0)
                    createWall(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f, 0.0f, 0.0f}, ECS::EntityType::PARED, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                else if (values[0].compare("Y") == 0)
                    createObjectEOL(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), ECS::EntityType::END_LEVEL, {std::stof(values[8]), std::stof(values[10]), std::stof(values[9])});
                else if (values[0].compare("Z") == 0)
                {
                    contZ++;
                    SB behav;
                    switch ((int)std::stof(values[4]))
                    {
                    case 1:
                    {
                        behav = SB::Arrive;
                    }
                    break;
                    case 2:
                    {
                        behav = SB::Seek;
                    }
                    break;
                    case 3:
                    {
                        behav = SB::Pathfollowing;
                    }
                    break;
                    default:
                    {
                        behav = SB::Arrive;
                    }
                    break;
                    }
                    // std::cout << "POS EN TXT: " << std::stof(values[1]) << ", " << std::stof(values[3]) << ", " << std::stof(values[2]) << std::endl;
                    // std::cout << "CREATE ZOMBIE**************" << std::endl;
                    /* auto e =  */ createEnemyZombie(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), {0.f, 0.5f, 0.f}, behav, bts.at(contZ), static_cast<float>(ptime));
                }
                else if(values[0].compare("X") == 0){
                    contZ++;
                    SB behav;
                    switch ((int)std::stof(values[4]))
                    {
                    case 1:
                    {
                        behav = SB::Arrive;
                    }
                    break;
                    case 2:
                    {
                        behav = SB::Seek;
                    }
                    break;
                    case 3:
                    {
                        behav = SB::Pathfollowing;
                    }
                    break;
                    default:
                    {
                        behav = SB::Arrive;
                    }
                    break;
                    }
                    // std::cout << "POS EN TXT: " << std::stof(values[1]) << ", " << std::stof(values[3]) << ", " << std::stof(values[2]) << std::endl;
                    /* auto e =  */ createEnemyEscarabajo(std::stof(values[1]), std::stof(values[2]), {0.f, 0.5f, 0.f}, behav, bts.at(contZ), static_cast<float>(ptime));
                }else if(values[0].compare("O") == 0){
                    contZ++;
                    SB behav;
                    switch ((int)std::stof(values[4]))
                    {
                    case 1:
                    {
                        behav = SB::Arrive;
                    }
                    break;
                    case 2:
                    {
                        behav = SB::Seek;
                    }
                    break;
                    case 3:
                    {
                        behav = SB::Pathfollowing;
                    }
                    break;
                    default:
                    {
                        behav = SB::Arrive;
                    }
                    break;
                    }
                    // std::cout << "POS EN TXT: " << std::stof(values[1]) << ", " << std::stof(values[3]) << ", " << std::stof(values[2]) << std::endl;
                    /* auto e =  */ createEnemyMomia(std::stof(values[1]), std::stof(values[3]), std::stof(values[2]), {0.f, 0.5f, 0.f}, behav, bts.at(contZ), static_cast<float>(ptime));
                }

                // else
                // createFloor(std::stof(values[1]), std::stof(values[3]),std::stof(values[2]), std::stof(values[4]), std::stof(values[6]), std::stof(values[5]), {0.0f,0.0f,0.0f}, ECS::EntityType::PARED);

                cont = 0;
                totalElements++;
            }
            cont++;

            texto.erase(0, pos + delimiter.length());
        }
    }

    // std::cout << "totalelementos: " << totalElements << "\n";

    // Leer el archivo JSON
    // ////////////////////////////////
    //  Cargo datos del player
    nlohmann::json datos_general;
    datos_general = manageData.leerJSON("./media/levels/general.json");

    if (m_EntMan.getEntityVector().size() > 0)
    {
        auto *player = m_EntMan.getPlayer();
        nlohmann::json datos;
        std::string concatenado = "./media/levels/";
        concatenado += datos_general["jugador"]["nivel_anterior"];
        concatenado += "/levelData.json";

        datos = manageData.leerJSON(concatenado);

        if (player && !(datos["jugador"].is_null()))
        {
            // player->setState(ECS::EntityState::IDLE);
            player->getComponent<HealthComponent>()->health = datos["jugador"]["vida_actual"];
            player->getComponent<ShotBehaviourComponent>()->shot_ammo = datos["jugador"]["balas"];
            for (auto &par : datos["jugador"]["inventario"].items())
            {
                // std::cout << "Clave: " << par.key() << ", Valor: " << par.value() << std::endl;
                player->getComponent<InventoryComponent>()->addElement(static_cast<ECS::EntityTAG>(std::stoi(par.key())), par.value());
            }
        }
    }

    return totalElements;
}