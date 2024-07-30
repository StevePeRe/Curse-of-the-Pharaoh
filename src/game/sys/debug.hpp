#pragma once
#include <ecs/util/globals.hpp>
#include <game/util/GameDataManager.hpp>
#include <unordered_map>
#include <vector>

namespace ECS
{
    struct EntityManager;
}

struct GraphicEngine;


struct DebugSystem
{
    explicit DebugSystem() {
        vecEntities.reserve(100);
    };

    void update(ECS::EntityManager &g, GraphicEngine &ge);
    void init(GraphicEngine &ge);

    std::string TextFormat(const char *format, ...);

private:
    bool close{true};
    bool init_{false};
    bool firstTime{true};
    bool player{false};
    bool filtered{false};

    // id ent
    int ID_ent{1};

    // cmps
    bool physics{false};
    bool render{false};
    bool inventory{false};
    bool health{false};
    bool perception{false};
    bool powerUp{false};
    bool shotBeh{false};

    // cmp propiedades

        // health
        float h_health{100.f};
        bool has_inmunity{false};
        float inmunityTime{.5f};

        // inv
        int add_ammo{0};
        int add_bigHeal{0};
        int add_smallHeal{0};

        // perc 
        bool p_sigth{false};
        bool use_raycast{false};
        bool show_raycast{false};
        bool addLayerPlayer{false};
        bool addLayerEnemy{false};
        bool addLayerEnviro{false};

        bool p_hearing{false};

        // phy
        bool show_forces{false};
        float changeSprintVel{0.f};
        
    // listas
    int entityTypeSelected{0};
    std::vector<std::size_t> vecEntities;
    const char *entityType[14]{ //mostrar en el combo
        "PLAYER",
        "BOX",
        "CAMERA",
        "ENEMY",
        "PICKABLE_OBJECT",
        "POWER_UP",
        "ELEVATOR",
        "DOOR_KEY",
        "DOOR_NO_KEY",
        "PILAR",
        "PARED",
        "PUZZLE_1",
        "PUZZLE_2",
        "END_LEVEL"
    };
    ECS::EntityType entityTypeList[14]{ // para luego buscar
        ECS::EntityType::PLAYER,
        ECS::EntityType::BOX,
        ECS::EntityType::CAMERA,
        ECS::EntityType::ENEMY,
        ECS::EntityType::PICKABLE_OBJECT,
        ECS::EntityType::POWER_UP,
        ECS::EntityType::ELEVATOR,
        ECS::EntityType::DOOR_KEY,
        ECS::EntityType::DOOR_NO_KEY,
        ECS::EntityType::PILAR,
        ECS::EntityType::PARED,
        ECS::EntityType::PUZZLE_1,
        ECS::EntityType::PUZZLE_2,
        ECS::EntityType::END_LEVEL
    };


    bool tps{false};
    float player_pos [3] {0.0f, 0.0f, 0.0f};
    float player_hitbox [2] {0.0f, 0.0f};
    float masa{0.0f};
    float restitucion{0.0f};
    bool gravedad{true};
    bool impulso{false};
    bool show_hitbox{false};
    float staticFriction{0.0f};
    float dynamicFriction{0.0f};
    GameDataManager manageData;

};