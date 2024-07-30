#pragma once
// libs
#include <iostream>
#include <cstdint>
#include <glm/vec2.hpp>

namespace ECS
{
    struct Vector3
    {
        float x, y, z;
    };

    // -------------------------------------------------------------------------------
    // enums
    typedef enum
    {
        NONE,       /* inactivo */
        // PICKABLE_OBJECTs
        PICKABLE_OBJECT,
        // PLAYABLE
        PLAYER,
        ENEMY,
        BOX,
        DOOR_KEY,
        DOOR_NO_KEY,
        BULLET,
        PILAR,
        PARED,
        PLANO,
        SUELO,
        SUELO_MUERTE,
        CAMERA,
        ELEVATOR,
        TRAP,
        END_LEVEL,
        // TRIGGERS
        POWER_UP,
        // PUZZLE
        PUZZLE_1,
        PUZZLE_2,
        PUZZLE_3,
        PUZZLE_4,
        PROJECTILE,
    } EntityType;

    typedef enum
    {
        IDLE,       /* inactivo */
        MOVING_RIGHT,
        MOVING_LEFT,
        MOVING_FORWARDS,
        MOVING_BACKWARDS, 
        MOVING_IA,
        MOVING_BOX,
        CROUCH,
        IDLE_CROUCH,
        C_OBJETO, 
        SHOTTING_PISTOL,
        SHOTTING_SHOTGUN,
        // DASHING
        // CAM Movements
        CAM_MOVING_LEFT,
        CAM_MOVING_RIGTH,
        CAM_MOVING_FORWARDS,
        CAM_MOVING_BACKWARDS,
        CAM_ROTATE_LEFT,
        CAM_ROTATE_RIGTH,
        CAM_ROTATE_FORWARDS,
        CAM_ROTATE_BACKWARDS,
        CAM_UP,
        CAM_DOWN,
        CAM_ZOOM_UP,
        CAM_ZOOM_DOWN,
        CAM_FOVY_UP,
        CAM_FOVY_DOWN,
        CAM_RESET
    } EntityState;

    typedef enum
    {
        NO_TAG = 0 << 0,
        E_PLAYER = 1 << 1,
        ENEMY_Z1 = 1 << 2,
        ENEMY_Z2 = 1 << 3,
        ARROW_T1 = 1 << 4,
        ARROW_T2 = 1 << 5,
        ARROW_T3 = 1 << 6,
        MOVIBLE_CAM = 1 << 7,
        KEY_1 = 1 << 8, 
        KEY_2 = 1 << 9,
        KEY_3 = 1 << 10,
        KEY_4 = 1 << 11,
        AMMO = 1 << 12,
        BIG_HEAL = 1 << 13,
        SMALL_HEAL = 1 << 14,
        INMUNITY = 1 << 15,
        SHOTGUNMODE = 1 << 16,
        CHANGEm_DUNGEON = 1 << 17,
        CHANGEm_EXTERIOR = 1 << 18,
    } EntityTAG; 

    typedef enum
    {
        NO_PLAYING   = 0 << 0,
        EXT_PLAYING  = 1 << 1,
        COMB_PLAYING = 1 << 2,
        DUNG_PLAYING = 1 << 3,
    } EventTAG;

    typedef enum{
        NONE_ELEVATOR,
        SWITCH_1,
        SWITCH_2,
    } SwitchType;

    typedef enum{
        NONE_DIRECTION,
        DIR_Y,
        DIR_X,
        DIR_Z
    } ElevatorDirection;

    typedef enum {
        NO_COLLISION,
        KEY_COLLISION,
        SMALL_HEAL_COLLISION,
        BIG_HEAL_COLLISION,
        AMMO_COLLISION,
    } InventoryObject;

    // Esto tendra que ir en el InputComponent o algo asi
    // Estas teclas estan en el fichero base del RayLib
    // Para cuando tengamos nuestro propio input modificaremos este ENUM
    typedef enum
    {
        KEY_NULL = 0,
        KEY_A = 65, // Key: A | a
        KEY_D = 68, // Key: D | d
        KEY_S = 83, // Key: S | s
        KEY_W = 87, // Key: W | w
    } KeyboardKey;

    // Players Behaviour
    typedef enum
    {
        IDLEB,       /* inactivo */
        Pistol, /* disparo pistola */
        ShotGun, /* disparo escopeta */
        Dart,   /* disparo dardo */
    } BehaviourType;

    typedef enum
    {
        // PARA EL JUGADOR
        IDLEB_S,       /* inactivo */
        SHOTTING,
        // PARA LAS BALAS
        DestroyP,   /* puesto para destruirse */
        DestroySG,   /* puesto para destruirse */
        DestroyD,   /* puesto para destruirse */
    } BehaviourState;

        // Angulos
    typedef enum
    {
        NORTH,
        WEST,
        EAST,
        SOUTH
    } ORIENTATION;

       // PUZZLES
    typedef enum
    {
        NONE_PUZZLE,
        // OBJETOS QUE INTERACCIONAN CON EL PUZZLE
        INTERACTION,
        // PUZZLE
        PUZ_1,
        PUZ_2,
        /* PUZ_3,
        PUZ_4,  */ 
        // PILARES
        PILARES,
        PILARES_1,
        PILARES_2,
        PILARES_3,
        PILARES_4,
        BOTONES,
        BOTONES_1,
        BOTONES_2,
        BOTONES_3,
        BOTONES_4,
        // ACERTIJOS
        /*ACERTIJOS,
         ACERTIJO_1,
        ACERTIJO_2,
        ACERTIJO_3, */
        // CAJAS
        /* CAJAS,
        CAJAS_1,
        CAJAS_2,
        CAJAS_3 */
    } PUZZLE_TYPE;

    // -------------------------------------------------------------------------------
    // constexpr

    static constexpr std::size_t MAX_ENTITIES{1000};

    constexpr std::size_t ID_jugador{1};

    // Strings
    constexpr char *TITLE = {const_cast<char *>("Curse of the Pharaoh")};

    // CUADRANTES
    // constexpr Vector3 CUADRANTE1_POS {}
    // constexpr Vector3 CAMERA_CUADRANTE_ESQUINA_AMARILLO_VERDE = { 19.221f, 07.962f, 19.217f };
    // constexpr Vector3 CAMERA_TARGET__ESQUINA_AMARILLO_VERDE = { 13.838f, 1.953f, 13.348f };
    // constexpr Vector3 CAMERA_CUADRANTE_ESQUINA_AMARILLO_VERDE = {17.921f, 06.062f, 17.817f};
    // constexpr Vector3 CAMERA_TARGET__ESQUINA_AMARILLO_VERDE = {13.838f, 1.953f, 13.348f};
    // constexpr Vector3 CAMERA_CUADRANTE_ESQUINA_AMARILLO_AZUL = {-19.221f, 07.962f, 19.217f};
    // constexpr Vector3 CAMERA_TARGET__ESQUINA_AMARILLO_AZUL = {-13.838f, 1.953f, 13.348f};
    // constexpr Vector3 CAMERA_CUADRANTE_ESQUINA_ROSA_AZUL = {-19.221f, 07.962f, -19.217f};
    // constexpr Vector3 CAMERA_TARGET__ESQUINA_ROSA_AZUL = {-13.838f, 1.953f, -13.348f};
    // constexpr Vector3 CAMERA_CUADRANTE_ESQUINA_ROSA_VERDE = { 19.221f, 07.962f, -19.217f };
    // constexpr Vector3 CAMERA_TARGET__ESQUINA_ROSA_VERDE = { 13.838f, 1.953f, -13.348f };
    // constexpr Vector3 CAMERA_CUADRANTE_ESQUINA_ROSA_VERDE = {13.353f, 02.669f, -19.217f};
    // // constexpr Vector3 CAMERA_TARGET__ESQUINA_ROSA_VERDE = {13.305f, 0.854f, -12.685f};
    
    // constexpr const float CAMERA_SPEED = 1.1f;
    // constexpr const float CAMERA_SPEED_ROTATION = 1.1f;
    // constexpr const float CAMERA_SPEED_ZOOM = 1.1f;
    // constexpr const float CAMERA_SPEED_FOVY = 1.1f;
    // constexpr const float CAMERA_SPEED_UP_DOWN = 1.1f;

    constexpr const float CAMERA_SPEED = 0.3f;
    constexpr const float CAMERA_SPEED_ROTATION = 0.01f;
    constexpr const float CAMERA_SPEED_ZOOM = 0.01f;
    constexpr const float CAMERA_SPEED_FOVY = 0.05f;
    constexpr const float CAMERA_SPEED_UP_DOWN = 0.3f;

    constexpr const Vector3 CAMERA_ARRIBA = { 00.497f, 32.629f, 01.499f };
    constexpr const Vector3 CAMERA_TARGET_ARRIBA = { 00.500f, 00.630f, 01.181f };

    constexpr const Vector3 CAMERA_CUADRANTE_ESQUINA_AMARILLO_VERDE = { 16.489f, 03.059f, 14.653f };
    constexpr const Vector3 CAMERA_TARGET__ESQUINA_AMARILLO_VERDE = { 10.868f, 0.972f, 14.414f };
    constexpr const Vector3 CAMERA_CUADRANTE_ESQUINA_AMARILLO_AZUL = { -14.653f, 03.059f, 16.489f };
    constexpr const Vector3 CAMERA_TARGET__ESQUINA_AMARILLO_AZUL = { -14.414f, 0.972f, 10.868f };
    constexpr const Vector3 CAMERA_CUADRANTE_ESQUINA_ROSA_AZUL = { -16.489f, 03.059f, -14.653f };
    constexpr const Vector3 CAMERA_TARGET__ESQUINA_ROSA_AZUL = { -10.868f, 0.972f, -14.414f };
    constexpr const Vector3 CAMERA_CUADRANTE_ESQUINA_ROSA_VERDE = { 14.653f, 03.059f, -16.489f };
    constexpr const Vector3 CAMERA_TARGET__ESQUINA_ROSA_VERDE = { 14.414f, 0.972f, -10.868f };
    constexpr const Vector3 CAMERA_CUADRANTE_HABITACION = { -9.979f, 03.710f, -9.813f };
    constexpr const Vector3 CAMERA_TARGET__HABITACION = { -2.596f, 01.611f, -1.142f };

    constexpr float LIMIT_POS = {17.5f};
    constexpr float LIMIT_NEG = {-17.5f};

    constexpr Vector3 CAMERA_POSITION = {-0.0404705f, 4.25905f, 5.70433f};
    constexpr Vector3 CAMERA_TARGET = {0.953981f, -11.0183f, -22.5289f};
    constexpr Vector3 CAMERA_UP = {-0.000f, 0.998f, -0.000f};
    // Camara Desde Arriba
    // constexpr Vector3 CAMERA_POSITION = {-2.488f, 52.878f, 01.279f};
    // constexpr Vector3 CAMERA_TARGET = {0.644f, 0.972f, 01.419f};
    // constexpr Vector3 CAMERA_UP = {0.644f, 0.972f, 01.419f};
    constexpr const float CAMERA_FOVY = {60.0f};
    constexpr const float CUADRANTE_SIZE = {6.0f};
    constexpr const float CUADRANTE_START = {0.0f};
    constexpr const int FPS = {60};

    constexpr const int ID_MOVABLE_CAM = 99;
    constexpr const int ID_INIT_CAM = 1;

    constexpr int ANCHOPANTALLA{1280};
    constexpr int ALTOPANTALLA{720};

    // componentes Singleton
    constexpr std::size_t IDSingleCMPEventM {1};
    constexpr std::size_t IDSingleCMPPuzzleM {2};
    constexpr std::size_t IDSingleCMPBlackBoard {3};
    constexpr std::size_t IDSingleCMPHUD {4};
    constexpr std::size_t IDSingleCMPCINEMATIC{5};

    // ai
    constexpr float aiIdleRange { 2.0f };
    [[maybe_unused]] static int currentlevel = 0;
}
