#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <cstdint>
#include <array>
//#include <game/ai/bt/behaviourtree.hpp>


struct BehaviourTree;

typedef enum{
    Seek, Arrive, Pathfollowing, Flee
}SB;

struct AIComponent : ECS::Component{
    explicit AIComponent(std::size_t eID) : ECS::Component(eID){};

    static std::size_t getComponentTypeID() noexcept{
        return static_cast<std::size_t>(7);
    }
    SB behaviour {};

    BehaviourTree* behaviourTree {};

    bool tactive { false };
    float tx { 0.0f }, tz { 0.0f };

    bool tidlemov { false };
    float tidlex { 0.0f }, tidlez { 0.0f };

    float idleRangeMaxx {};
    float idleRangeMaxz {};
    float idleRangeMinx {};
    float idleRangeMinz {};

    static constexpr float time2arrive { 7.5f };
    float arrivalRadius;// para check_next_to_jes
    static constexpr float noticeRadius  { 6.0f };  // 9, para check_close
    static constexpr float farRadius     {18.0f };     // 12, para check_far

    static constexpr float maxYDifference { 2.0f };

    int enemyType { 0 }; // 1-> zombie ; 2->escarabajo ; 3->momia ; 4->momia laberinto

    float damage {};

    static constexpr float evadeRadius { 1.2f };
    static constexpr float flockRadius { 1.5f };

    bool running { false };
    int currentNode {0};
    float distPlayer {0.0f};
    bool detectedPlayer { false };

    float vX { 0.f };    
    float vZ { 0.f };

    bool onPatrol { true };
    bool patrolInterrupted { false };

    //perception time /cooldown
    float perceptionTime { 0.0f };
    float accumulatedDt { 0.0f }; //dt->deltatime

    
};