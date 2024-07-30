#pragma once
//lib
#include <vector>
// managers
#include <ecs/man/entitymanager.hpp>
//util
#include "waypoints.hpp"
#include <game/ai/sb/stbeh.hpp>
//cmp
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/aiComponent.hpp>
#include "pathComponent.hpp"

struct PathfollowingSys{

    explicit PathfollowingSys() = default;
    void update(ECS::EntityManager &em, PathComponent& pathcomp, PhysicsComponent& phy, int lvl);

    void setPath(PhysicsComponent& phy, std::vector<float> currentPos, std::vector<float> targetPos, PathComponent& pathcomp, int lvl);

    void setStartAndGoal(PathComponent& pathcomp, std::vector<float> prevstart, std::vector<float> prevgoal, int lvl);

    Steer continuePath(PathComponent& pathcomp, PhysicsComponent& phy, int lvl);
    
    Waypoint* findStartWaypoint(std::vector<float> currentPos, std::vector<float> goalPos, int lvl);
    Waypoint* findGoalWaypoint(std::vector<float> goalPos, int lvl);
    void loadLevelWaypoints(int lvl);
    void setPathGs(PathComponent pc, int lvl);
    void setPathHs(PathComponent pc, int lvl);
    bool isInPathToGoal(Waypoint* wp, PathComponent pc);
    bool isOnReturnPath(Waypoint* wp, PathComponent pc);
    Waypoint* findNextPathPoint(PathComponent& pathcomp, int lvl);
    Waypoint* getCurrentWp(PathComponent& pathcomp, int lvl);
    bool hasBeenVisited(PathComponent& pathcomp,int id);

    Waypoint* getLvlWaypoint(int n, int lvl);

    void moveEnemy(PathComponent& pathcomp, PhysicsComponent& phy, AIComponent& ai);

    void setPatrolMomia(PathComponent& pc, PhysicsComponent& phy, AIComponent& ai);
    // void setPatrolMomia2(PathComponent& pc);

    void setStartAndGoalWP(PathComponent& pathcomp, Waypoint* prevstart, Waypoint* prevgoal, int lvl);  
    void findReturnRoute(ECS::EntityManager &em, PathComponent& pathcomp, PhysicsComponent& phy, AIComponent& ai, int lvl);
    Steer continueReturnPath(PathComponent& pathcomp, int lvl);
    void freeMovement(PhysicsComponent& phy, AIComponent& ai);

    static std::vector<Waypoint> waypointsLvl0;
    static std::vector<Waypoint> waypointsLvl1;
    static std::vector<Waypoint> waypointsLvl2;
    int currentWpId {-1};
    float waypointArriveRadius { 0.3f };

//  ORDEN:
//  
//                     
//
//
        
};