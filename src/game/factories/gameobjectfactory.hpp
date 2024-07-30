 #pragma once
// util
#include <ecs/util/globals.hpp>
// cmp
#include <game/cmp/aiComponent.hpp>
// util
#include <game/util/GameDataManager.hpp>
// libs
#include <cstdint>
//#include <raylib.h>
#include <vector>
#include <fstream>
#include <string>
#include <glm/glm.hpp>


namespace ECS
{
    struct EntityManager;
    struct Entity;
}

struct GameDataManager;
struct GraphicEngine;

struct AudioEngine;

struct GameObjectFactory
{
    explicit GameObjectFactory(ECS::EntityManager &em, GraphicEngine &ge, AudioEngine &au)
        : m_EntMan(em), GE(ge), audio(au)
    {

    }

    // ECS::Entity &createSpawner();
    template <typename CALLABLE_t>
    ECS::Entity &createSpawner(float x, float y, float z, ECS::EntityType type, CALLABLE_t callback) const;
    ECS::Entity &createPlayer(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, glm::vec3 rotation) const;
    ECS::Entity &createShot(float x, float y, float z, float w, float h, float d, ECS::BehaviourState state, int16_t shot_damage, uint32_t distance_toDo, glm::vec3 direction) const;
    // metodo de gun, pero se deben crear las animaciones de cuando no tienes arma
    ECS::Entity &createEnemyZombie(float x, float y, float z, glm::vec3 c, SB sbt, BehaviourTree *bt, float pt);
    ECS::Entity &createEnemyEscarabajo(float x, float z, glm::vec3 c, SB sbt, BehaviourTree *bt, float pt);
    ECS::Entity &createEnemyMomia(float x, float y, float z, glm::vec3 c, SB sbt, BehaviourTree *bt, float pt);
    ECS::Entity &createEnemyMomiaLaberinto(float x, float y, float z, glm::vec3 c, SB sbt, BehaviourTree *bt, float pt);
    ECS::Entity &createEnemyArrow(float x, float z, float tx, float tz, glm::vec3 c);
    ECS::Entity &createObject(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, std::string fileName, std::string texture, glm::vec3 rotation, ECS::EntityTAG tag = ECS::EntityTAG::NO_TAG) const;
    ECS::Entity &createObjectEOL(float x, float y, float z, float w, float h, float d, ECS::EntityType type, glm::vec3 rotation) const; // END OF LEVEL
    ECS::Entity &createObject4movement(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, glm::vec3 rotation, float mass) const;
    ECS::Entity &createDoor(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityTAG keyTag, ECS::EntityType doorType, glm::vec3 rotation) const;
    ECS::Entity &createKey(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, glm::vec3 rotation, std::string fileName, std::string texture, ECS::EntityTAG tag = ECS::EntityTAG::NO_TAG) const;
    ECS::Entity &createObject4Objective(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, glm::vec3 rotation) const;
    ECS::Entity &createWall(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, glm::vec3 rotation) const;
    ECS::Entity &createRoof(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, glm::vec3 rotation) const;
    ECS::Entity &createFloor(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, glm::vec3 rotation) const;
    ECS::Entity &createSpawnFloor(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::EntityType type, std::string fileName, std::string texture, glm::vec3 rotation) const;
    ECS::Entity &createMessage(float x, float y, float z, float w, float h, float d, const char* message) const;
    ECS::Entity &createElevator(float x, float y, float z, float w, float h, float d, float distance, bool direction, ECS::SwitchType switchType, ECS::ElevatorDirection sense, std::string fileName, std::string texture) const;
    ECS::Entity &createSwitch(float x, float y, float z, float w, float h, float d, ECS::SwitchType switchType, std::string fileName, std::string texture, glm::vec3 rotation) const;
    ECS::Entity &createCamera(int idCam, float xPos, float yPos, float zPos, float xTar, float yTarg, float zTar,
                                float xBox, float yBox, float zBox, float w, float h, float d, glm::vec3 color, int orientation,
                                float fovy, ECS::EntityType type, ECS::EntityTAG tag = ECS::EntityTAG::NO_TAG) const;
    // TRIGGERS
    ECS::Entity &createTrigger(float x, float y, float z, float w, float h, float d, ECS::EntityType type, std::string fileName, std::string texture, [[maybe_unused]] glm::vec3 rotation, ECS::EntityTAG tag) const;
    ECS::Entity &createArrowTrap(float x, float y, float z, float w, float h, float d, ECS::EntityType type, ECS::EntityTAG tag) const;

    // LEER DATOS PLAYER

    // INITS
    void initLevel(const std::string nivel);
    void initPuzzlesLevel(const std::string nivel);
    void initMessagesLevel(const std::string nivel);
    void initBehaviourTrees();
    /* void initDoorsLevel(const std::string nivel); */
    uint64_t loadModelsDataFromTxt(std::string filePath, glm::vec3 c);

    // PUZZLES
    ECS::Entity &createObject4PuzzleClosely(float x, float y, float z, float w, float h, float d, bool popUpE, glm::vec3 c, ECS::PUZZLE_TYPE type, ECS::PUZZLE_TYPE puzzleType, std::string fileName, std::string texture, glm::vec3 rotation) const;
    ECS::Entity &createObject4Puzzle(float x, float y, float z, float w, float h, float d, glm::vec3 c, ECS::PUZZLE_TYPE type, ECS::PUZZLE_TYPE puzzleType, std::string fileName, std::string texture) const;    
    ECS::Entity &createRangeCube4Puzzle(float x, float y, float z, float w, float h, float d, ECS::EntityType type) const;

private:
    ECS::EntityManager &m_EntMan;
    GraphicEngine &GE;
    AudioEngine &audio;
    GameDataManager manageData;
    float escarabajoY = 2.f;
    std::vector<BehaviourTree*> bts;
    int idTree {++baseid};
    int baseid = -1;
};
