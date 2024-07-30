#pragma once
#include <vector>
#include "waypoints.hpp"
#include <ecs/cmp/component.hpp>


struct PathComponent : ECS::Component{
    explicit PathComponent(std::size_t eID):Component(eID){};
    static int getComponentTypeID() noexcept{
        return static_cast<std::size_t>(12);
    }

    bool active { false };
    // int collide { 0 };

    // std::vector<float> referencePos{ 0.0f, 0.0f };
    // std::vector<float> atascadoPos{  0.0f, 0.0f };

    bool initializedStartAndGoal { false };
    bool foundGoal { false };
    Waypoint* startCell;
    Waypoint* goalCell;
    // std::vector<Waypoint*> openList;
    std::vector<Waypoint*> visitedList;
    std::vector<Waypoint*> pathToGoal;

    bool patrolInitialized { false };
    std::vector<Waypoint*> patrolRoute;
    Waypoint* currentGoal { nullptr };
    // float vX {0.f};
    // float vZ {0.f};    
    std::vector<Waypoint*> patrolRouteReturn;
    bool foundReturnGoal { false };
    bool en1 {false};

    bool hasReachedStart { false };
    bool hasReachedGoal  { false };
};