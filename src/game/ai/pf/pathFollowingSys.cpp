#include "pathFollowingSys.hpp"

std::vector<Waypoint> PathfollowingSys::waypointsLvl0;
std::vector<Waypoint> PathfollowingSys::waypointsLvl1;
std::vector<Waypoint> PathfollowingSys::waypointsLvl2;

void PathfollowingSys::update(ECS::EntityManager &em, PathComponent& pathcomp, PhysicsComponent& phy, int lvl){
    Steer st;

    auto entid = phy.getEntityID();
    auto ent1 = em.getEntityByID(entid);
    auto ai = ent1->getComponent<AIComponent>();

    std::vector<float> posactual { phy.position.x, phy.position.z };
    std::vector<float> postarget { ai->tx, ai->tz };

    setPath(phy, posactual, postarget, pathcomp, lvl);
    while(!pathcomp.foundGoal){
        continuePath(pathcomp, phy, lvl);
    }
}

void PathfollowingSys::findReturnRoute(ECS::EntityManager &em, PathComponent& pathcomp, PhysicsComponent& phy, AIComponent& ai, int lvl){
    pathcomp.visitedList.clear();
    pathcomp.patrolRouteReturn.clear();

    Waypoint* pointToReturnTo;

    for(int i=0; i<(int)pathcomp.patrolRoute.size(); i++){
        if(pathcomp.patrolRoute.at(i)->visited == false){
            pointToReturnTo = pathcomp.patrolRoute.at(i);
            break;
        }
    }

    Waypoint* start = findStartWaypoint({phy.position.x, phy.position.z}, {pointToReturnTo->Xcoord, pointToReturnTo->Zcoord}, lvl);
    
    setStartAndGoalWP(pathcomp, start, pointToReturnTo, lvl);
    if(pathcomp.startCell == pathcomp.goalCell){
        if(pathcomp.startCell == pathcomp.goalCell){
        pathcomp.patrolRouteReturn.push_back(pathcomp.goalCell); 
        pathcomp.foundGoal = true;
        return;
    }
    }
    pathcomp.initializedStartAndGoal = true;

    while(!pathcomp.foundGoal){
        continueReturnPath(pathcomp, lvl);
    }
}

Steer PathfollowingSys::continueReturnPath(PathComponent& pathcomp, int lvl){
    Steer st;

    Waypoint* nextCell = findNextPathPoint(pathcomp, lvl);

    if( nextCell->id == pathcomp.goalCell->id ){
        pathcomp.goalCell->idPrev = (int)pathcomp.visitedList.at(pathcomp.visitedList.size()-1)->id;
        pathcomp.visitedList.push_back(nextCell);

        for(int i=0; i<(int)pathcomp.visitedList.size(); i++){
            if(pathcomp.visitedList.at(i)->idPrev != 0 && !isOnReturnPath(pathcomp.visitedList.at(i), pathcomp)){
                pathcomp.patrolRouteReturn.push_back(pathcomp.visitedList.at(i));
            }
        }

        pathcomp.foundGoal = true;
        st.linearVX = nextCell->Xcoord;
        st.linearVZ = nextCell->Zcoord;        
    }
    else{
        nextCell->idPrev = currentWpId;
        pathcomp.visitedList.push_back(nextCell);
        currentWpId = (int)nextCell->id;
    }
    return st;
}

void PathfollowingSys::setPathGs(PathComponent pc, int lvl){
    // std::cout << "setpathg" << std::endl;
    //switch(lvl){
    //    case 0:
    //        for(int i=0; i<(int)waypointsLvl0.size(); i++){
    //            float distx = std::fabs(waypointsLvl0.at(i).Xcoord - pc.startCell->Xcoord);
    //            float distz = std::fabs(waypointsLvl0.at(i).Zcoord - pc.startCell->Zcoord);
    //            waypointsLvl0.at(i).G = (distx + distz);
    //        }
    //    break;
    //    case 1:
    //        for(int i=0; i<(int)waypointsLvl1.size(); i++){
    //            float distx = std::fabs(waypointsLvl1.at(i).Xcoord - pc.startCell->Xcoord);
    //            float distz = std::fabs(waypointsLvl1.at(i).Zcoord - pc.startCell->Zcoord);
    //            waypointsLvl1.at(i).G = (distx + distz);
    //        }
    //    break;
    //    case 2:
            for(int i=0; i<(int)waypointsLvl2.size(); i++){
                float distx = std::fabs(waypointsLvl2.at(i).Xcoord - pc.startCell->Xcoord);
                float distz = std::fabs(waypointsLvl2.at(i).Zcoord - pc.startCell->Zcoord);
                waypointsLvl2.at(i).G = (distx + distz);
            }
    //    break;
    //}
}

void PathfollowingSys::setPathHs(PathComponent pc, int lvl){
    // std::cout << "setpathH" << std::endl;
    //switch(lvl){
    //    case 0:
    //        for(int i=0; i<(int)waypointsLvl0.size(); i++){
    //            float distx = std::fabs(waypointsLvl0.at(i).Xcoord - pc.goalCell->Xcoord);
    //            float distz = std::fabs(waypointsLvl0.at(i).Zcoord - pc.goalCell->Zcoord);
    //            waypointsLvl0.at(i).H = (distx + distz);
    //        }
    //    break;
    //    case 1:
    //        for(int i=0; i<(int)waypointsLvl1.size(); i++){
    //            float distx = std::fabs(waypointsLvl1.at(i).Xcoord - pc.goalCell->Xcoord);
    //            float distz = std::fabs(waypointsLvl1.at(i).Zcoord - pc.goalCell->Zcoord);
    //            waypointsLvl1.at(i).H = (distx + distz);
    //        }
    //    break;
    //    case 2:
            for(int i=0; i<(int)waypointsLvl2.size(); i++){
                float distx = std::fabs(waypointsLvl2.at(i).Xcoord - pc.goalCell->Xcoord);
                float distz = std::fabs(waypointsLvl2.at(i).Zcoord - pc.goalCell->Zcoord);
                waypointsLvl2.at(i).H = (distx + distz);
            }
    //    break;
    //}
}

void PathfollowingSys::setPath([[maybe_unused]]PhysicsComponent& phy, std::vector<float> currentpos, std::vector<float> targetPos, PathComponent& pathcomp, int lvl){
    // std::cout << "setPath" << std::endl;
    if( !pathcomp.initializedStartAndGoal ){

        pathcomp.visitedList.clear();
        pathcomp.pathToGoal.clear();

        std::vector<float> start; //La pos debe ser la posicion de la matriz
        start.push_back(currentpos.at(0));
        start.push_back(currentpos.at(1));

        std::vector<float> goal; //La pos debe ser la posicion de la matriz
        goal.push_back(targetPos.at(0));
        goal.push_back(targetPos.at(1));

        pathcomp.foundGoal = false;
        setStartAndGoal(pathcomp, start, goal, lvl);
        pathcomp.initializedStartAndGoal = true;
    }
}

void PathfollowingSys::setStartAndGoal(PathComponent& pathcomp, std::vector<float> prevstart, std::vector<float> prevgoal, int lvl){  
    pathcomp.startCell = findStartWaypoint(prevstart, prevgoal, lvl);
    pathcomp.goalCell = findGoalWaypoint(prevgoal, lvl);
    // std::cout << "** STARTCELL ** : " << pathcomp.startCell->id << std::endl;
    // std::cout << "** GOALCELL ** : " << pathcomp.goalCell->id << std::endl;
    if(pathcomp.startCell == pathcomp.goalCell){
        pathcomp.pathToGoal.push_back(pathcomp.goalCell); 
        pathcomp.foundGoal = true;
        return;
    }

    pathcomp.startCell->idPrev = -1;
    setPathGs(pathcomp, lvl);
    setPathHs(pathcomp, lvl);

    pathcomp.pathToGoal.push_back(pathcomp.startCell);
    pathcomp.visitedList.push_back(pathcomp.startCell);

    currentWpId = (int)pathcomp.startCell->id;
}

void PathfollowingSys::setStartAndGoalWP(PathComponent& pathcomp, Waypoint* prevstart, Waypoint* prevgoal, int lvl){  
    pathcomp.startCell = prevstart;
    pathcomp.goalCell = prevgoal;
    // std::cout << "** ret START ** : " << pathcomp.startCell->id << std::endl;
    // std::cout << "** ret GOAL ** : " << pathcomp.goalCell->id << std::endl;

    pathcomp.startCell->idPrev = -1;
    setPathGs(pathcomp, lvl);
    setPathHs(pathcomp, lvl);

    pathcomp.patrolRouteReturn.push_back(pathcomp.startCell);
    pathcomp.visitedList.push_back(pathcomp.startCell);

    currentWpId = (int)pathcomp.startCell->id;
}

Waypoint* PathfollowingSys::findStartWaypoint(std::vector<float> currentPos, std::vector<float> goalPos, int lvl){
    // std::cout << "findclosestwaypointtopos" << std::endl;
    Waypoint* wp1 = nullptr;
    Waypoint* wp2 = nullptr;
    float mindist = 99999.99f;
    float dist1;
    float dist2;    
    int id = -1;
    //switch(lvl){
    //    case 0:
    //        for(int i=0; i<(int)waypointsLvl0.size(); i++){
    //            float xdist = waypointsLvl0.at(i).Xcoord - currentPos.at(0);
    //            float zdist = waypointsLvl0.at(i).Zcoord - currentPos.at(1);
    //            float dist = sqrt((xdist*xdist)+(zdist*zdist));
    //            if(dist <= mindist){
    //                mindist = dist;
    //                id = (i);
    //            }
    //        }
    //        wp = &waypointsLvl0.at(id);
    //    break;
    //    case 1:
    //        for(int i=0; i<(int)waypointsLvl1.size(); i++){
    //            float xdist = waypointsLvl1.at(i).Xcoord - currentPos.at(0);
    //            float zdist = waypointsLvl1.at(i).Zcoord - currentPos.at(1);
    //            float dist = sqrt((xdist*xdist)+(zdist*zdist));
    //            if(dist <= mindist){
    //                mindist = dist;
    //                id = (i);
    //            }
    //        }
    //        wp = &waypointsLvl1.at(id);
    //    break;
    //    case 2:
            // std::cout << "FINDSTARTWAYPOINT lvl 2 num de wps: " << waypointsLvl2.size() << std::endl;
            for(int i=0; i<(int)waypointsLvl2.size(); i++){
                float xdist = waypointsLvl2.at(i).Xcoord - currentPos.at(0);
                float zdist = waypointsLvl2.at(i).Zcoord - currentPos.at(1);
                float dist = sqrt((xdist*xdist)+(zdist*zdist));
                if(dist <= mindist){ mindist = dist; id = (i); }
            }
            wp1 = &waypointsLvl2.at(id);
            dist1 = std::sqrt((goalPos.at(0) - wp1->Xcoord)*((goalPos.at(0) - wp1->Xcoord)) + ((goalPos.at(1) - wp1->Zcoord)*(goalPos.at(1) - wp1->Zcoord))); 
            mindist = 99999.f;
            for(int j=0; j<(int)waypointsLvl2.size(); j++){
                float xdist = waypointsLvl2.at(j).Xcoord - currentPos.at(0);
                float zdist = waypointsLvl2.at(j).Zcoord - currentPos.at(1);
                float dist = sqrt((xdist*xdist)+(zdist*zdist));
                if(dist <= mindist && waypointsLvl2.at(j).id != wp1->id){ 
                    // std::cout << "++++ wp2.at vs wp1: " << waypointsLvl2.at(j).id << ", " << wp1->id << std::endl;
                     mindist = dist; id = (j); }
            }
            wp2 = &waypointsLvl2.at(id);
            dist2 = std::sqrt((goalPos.at(0) - wp2->Xcoord)*((goalPos.at(0) - wp2->Xcoord)) + ((goalPos.at(1) - wp2->Zcoord)*(goalPos.at(1) - wp2->Zcoord))); ;
            // std::cout << "++++ WPS ELEGIDOS: " << wp1->id << ", " << wp2->id << std::endl;
            if(dist1<dist2){ return wp1; }
            else{ return wp2; }


    //    break;
    //}
    // return wp;
}

Waypoint* PathfollowingSys::findGoalWaypoint(std::vector<float> goalPos, int lvl){
     // std::cout << "findclosestwaypointtopos" << std::endl;
    Waypoint* wp = nullptr;
    float mindist = 99999.99f;
    int id = -1;
    //switch(lvl){
    //    case 0:
    //        for(int i=0; i<(int)waypointsLvl0.size(); i++){
    //            float xdist = waypointsLvl0.at(i).Xcoord - currentPos.at(0);
    //            float zdist = waypointsLvl0.at(i).Zcoord - currentPos.at(1);
    //            float dist = sqrt((xdist*xdist)+(zdist*zdist));
    //            if(dist <= mindist){
    //                mindist = dist;
    //                id = (i);
    //            }
    //        }
    //        wp = &waypointsLvl0.at(id);
    //    break;
    //    case 1:
    //        for(int i=0; i<(int)waypointsLvl1.size(); i++){
    //            float xdist = waypointsLvl1.at(i).Xcoord - currentPos.at(0);
    //            float zdist = waypointsLvl1.at(i).Zcoord - currentPos.at(1);
    //            float dist = sqrt((xdist*xdist)+(zdist*zdist));
    //            if(dist <= mindist){
    //                mindist = dist;
    //                id = (i);
    //            }
    //        }
    //        wp = &waypointsLvl1.at(id);
    //    break;
    //    case 2:
            // std::cout << "FINDGOALWAYPOINT lvl 2 num de wps: " << waypointsLvl2.size() << std::endl;
            for(int i=0; i<(int)waypointsLvl2.size(); i++){
                float xdist = waypointsLvl2.at(i).Xcoord - goalPos.at(0);
                float zdist = waypointsLvl2.at(i).Zcoord - goalPos.at(1);
                float dist = sqrt((xdist*xdist)+(zdist*zdist));
                if(dist <= mindist){
                    // std::cout << "nuevo mindist: " << dist << std::endl;
                    mindist = dist;
                    id = (i);
                }
            }
            wp = &waypointsLvl2.at(id);
    //    break;
    //}
    return wp;
}

Waypoint* PathfollowingSys::getCurrentWp([[maybe_unused]]PathComponent& pathcomp, int lvl){
    // std::cout << "getcurrentwp: " << currentWpId << std::endl;
    Waypoint* wp= nullptr;
    //switch(lvl){
    //    case 0:
    //        for(int i=0; i<(int)waypointsLvl0.size(); i++){
    //            if((int)waypointsLvl0.at(i).id == currentWpId){
    //                wp = &waypointsLvl0.at(i);
    //            }
    //        }
    //    break;
    //    case 1:
    //        for(int i=0; i<(int)waypointsLvl1.size(); i++){
    //            if((int)waypointsLvl1.at(i).id == currentWpId){
    //                wp = &waypointsLvl1.at(i);
    //            }
    //        }
    //    break;
    //    case 2:
            for(int i=0; i<(int)waypointsLvl2.size(); i++){
                if((int)waypointsLvl2.at(i).id == currentWpId){
                    wp = &waypointsLvl2.at(i);
                }
            }
    //    break;
    //}
    // std::cout << "return wp con id " << wp->id << std::endl;
    return wp;
}

Waypoint* PathfollowingSys::getLvlWaypoint(int id, int lvl){
    // std::cout << "getlvlwaypoint" << std::endl;
    Waypoint* wp = nullptr;
    //switch(lvl){
    //    case 0:
    //        for(int i=0; i<(int)waypointsLvl0.size(); i++){
    //            if((int)waypointsLvl0.at(i).id == id){
    //                wp = &waypointsLvl0.at(i);
    //            }
    //        }
    //    break;
    //    case 1:
    //        for(int i=0; i<(int)waypointsLvl1.size(); i++){
    //            if((int)waypointsLvl1.at(i).id == id){
    //                wp = &waypointsLvl1.at(i);
    //            }
    //        }
    //    break;
    //    case 2:
            for(int i=0; i<(int)waypointsLvl2.size(); i++){
                if((int)waypointsLvl2.at(i).id == id){
                    wp = &waypointsLvl2.at(i);
                }
            }
    //    break;
    //}
    return wp;
}

Waypoint* PathfollowingSys::findNextPathPoint(PathComponent& pathcomp, int lvl){
    float bestF = 99999.f;
    int cellIndex = -1;

    Waypoint* currentwp_st = getCurrentWp(pathcomp, lvl);

    for( int i = 0; i<(int)currentwp_st->connectedWaypoints.size(); i++ ){
        int wpid = currentwp_st->connectedWaypoints.at(i);
        
        Waypoint* conn_wp_at_i = getLvlWaypoint(wpid, lvl);
        if(conn_wp_at_i->getF() < bestF && conn_wp_at_i->getF()>0 && !hasBeenVisited(pathcomp, wpid)){
            bestF = conn_wp_at_i->getF();
            cellIndex = i;
        }
    }

    Waypoint* bb = nullptr;
    if(cellIndex>=0){
        bb = getLvlWaypoint(currentwp_st->connectedWaypoints.at(cellIndex), lvl);
    }
    
    return bb;
}

bool PathfollowingSys::hasBeenVisited(PathComponent& pathcomp, int id){
    bool tf = false;
    for(int i=0; i<(int)pathcomp.visitedList.size(); i++){
        if(pathcomp.visitedList.at(i)->id == id){
            tf = true;
        }
    }
    return tf;
}

Steer PathfollowingSys::continuePath(PathComponent& pathcomp, [[maybe_unused]]PhysicsComponent& phy, int lvl){
    Steer st;

    Waypoint* nextCell = findNextPathPoint(pathcomp, lvl);

    if( nextCell->id == pathcomp.goalCell->id ){
        pathcomp.goalCell->idPrev = (int)pathcomp.visitedList.at(pathcomp.visitedList.size()-1)->id;
        pathcomp.visitedList.push_back(nextCell);

        for(int i=0; i<(int)pathcomp.visitedList.size(); i++){
            if(pathcomp.visitedList.at(i)->idPrev != 0 && !isInPathToGoal(pathcomp.visitedList.at(i), pathcomp)){
                pathcomp.pathToGoal.push_back(pathcomp.visitedList.at(i));
            }
        }

        pathcomp.foundGoal = true;
        st.linearVX = nextCell->Xcoord;
        st.linearVZ = nextCell->Zcoord;        
    }
    else{
        nextCell->idPrev = currentWpId;
        pathcomp.visitedList.push_back(nextCell);
        currentWpId = (int)nextCell->id;
    }
    return st;
}

bool PathfollowingSys::isInPathToGoal(Waypoint* wp, PathComponent pc){
    bool tf = false;
    for(int i=0; i<(int)pc.pathToGoal.size(); i++){
        if(wp->id == pc.pathToGoal.at(i)->id){
            tf = true;
        }
    }
    return tf;
}

bool PathfollowingSys::isOnReturnPath(Waypoint* wp, PathComponent pc){
    bool tf = false;
    for(int i=0; i<(int)pc.patrolRouteReturn.size(); i++){
        if(wp->id == pc.patrolRouteReturn.at(i)->id){
            tf = true;
        }
    }
    return tf;
}

void PathfollowingSys::setPatrolMomia(PathComponent& pc, PhysicsComponent& phy, AIComponent& ai){
    switch(pc.en1){
        case true:
            pc.patrolRoute.push_back(&waypointsLvl2.at(11));
            pc.patrolRoute.push_back(&waypointsLvl2.at(12));
            pc.patrolRoute.push_back(&waypointsLvl2.at(13));
            pc.patrolRoute.push_back(&waypointsLvl2.at(14));
            pc.patrolRoute.push_back(&waypointsLvl2.at(15));
            pc.patrolRoute.push_back(&waypointsLvl2.at(16));
            pc.patrolRoute.push_back(&waypointsLvl2.at(17));
            pc.patrolRoute.push_back(&waypointsLvl2.at(21));
            pc.patrolRoute.push_back(&waypointsLvl2.at(28));
            pc.patrolRoute.push_back(&waypointsLvl2.at(27));
            pc.patrolRoute.push_back(&waypointsLvl2.at(26));
            pc.patrolRoute.push_back(&waypointsLvl2.at(25));
            pc.patrolRoute.push_back(&waypointsLvl2.at(24));
            pc.patrolRoute.push_back(&waypointsLvl2.at(23));
            pc.patrolRoute.push_back(&waypointsLvl2.at(22));
            pc.patrolRoute.push_back(&waypointsLvl2.at(18));  
        break;
        case false:
            pc.patrolRoute.push_back(&waypointsLvl2.at(33));
            pc.patrolRoute.push_back(&waypointsLvl2.at(34));
            pc.patrolRoute.push_back(&waypointsLvl2.at(35));
            pc.patrolRoute.push_back(&waypointsLvl2.at(36));
            pc.patrolRoute.push_back(&waypointsLvl2.at(37));
            pc.patrolRoute.push_back(&waypointsLvl2.at(38));
            pc.patrolRoute.push_back(&waypointsLvl2.at(39));
            pc.patrolRoute.push_back(&waypointsLvl2.at(43));
            pc.patrolRoute.push_back(&waypointsLvl2.at(50));
            pc.patrolRoute.push_back(&waypointsLvl2.at(49));
            pc.patrolRoute.push_back(&waypointsLvl2.at(48));
            pc.patrolRoute.push_back(&waypointsLvl2.at(47));
            pc.patrolRoute.push_back(&waypointsLvl2.at(46));
            pc.patrolRoute.push_back(&waypointsLvl2.at(45));
            pc.patrolRoute.push_back(&waypointsLvl2.at(44));
            pc.patrolRoute.push_back(&waypointsLvl2.at(40));  
        break;
    }
    for(int i=0;i<(int)pc.patrolRoute.size();i++){
        pc.patrolRoute.at(i)->visited = false;
    }
    pc.patrolInitialized = true; 
    pc.currentGoal = pc.patrolRoute.at(0);
    float distanceX = (pc.currentGoal->Xcoord - phy.position.x);
    float distanceZ = (pc.currentGoal->Zcoord - phy.position.z);

    if(distanceX>1){ ai.vX = distanceX/5.f;  }
    else{            ai.vX = distanceX/2.f;  }
    if(distanceZ>1){ ai.vZ = distanceZ/5.f;  }
    else{            ai.vZ = distanceZ/2.f;  }
}

void PathfollowingSys::loadLevelWaypoints(int lvl){
    if(waypointsLvl2.size() > 0){ return; }
    std::vector<Waypoint> aux;
    std::vector<std::vector<int>> aux2;
    for(int i=0; i<62;i++){
        Waypoint wp;
        aux.push_back(wp);

        std::vector<int> con;
        aux2.push_back(con);
    }

    //switch(lvl){
    //    case 0:
    //
    //    break;
    //    case 1:
    //
    //    break;
    //    case 2:
        // std::cout<< "WPS nivel 2 ******************+" << std::endl;

            for(int i=0; i<62;i++){
                if(i<7){ aux.at(i).Zcoord = -60.2f; }
                else if(i<11){ aux.at(i).Zcoord = -55.1f; }
                else if(i<18){ aux.at(i).Zcoord = -50.5f; }
                else if(i<22){ aux.at(i).Zcoord = -45.4f; }
                else if(i<29){ aux.at(i).Zcoord = -40.8f; }
                else if(i<33){ aux.at(i).Zcoord = -35.7f; }
                else if(i<40){ aux.at(i).Zcoord = -31.3f; }
                else if(i<44){ aux.at(i).Zcoord = -26.2f; }
                else if(i<51){ aux.at(i).Zcoord = -21.4f; }
                else if(i<55){ aux.at(i).Zcoord = -16.4f; }
                else{ aux.at(i).Zcoord = -11.7f; }

                if(i==0 || i==7 || i==11 || i==18 || i==22 || i==29 || i==33 || i==40 || i==44 || i==51 || i==55){
                    aux.at(i).Xcoord = 29.8f; }
                else if(i==1 || i==12 || i==23 || i==34 || i==45 || i==56){
                    aux.at(i).Xcoord = 34.05f; }
                else if(i==2 || i==8 || i==13 || i==19 || i==24 || i==30 || i==35 || i==41 || i==46 || i==52 || i==57){
                    aux.at(i).Xcoord = 38.4f; }
                else if(i==3 || i==14 || i==25 || i==36 || i==47 || i==58){
                    aux.at(i).Xcoord = 43.f; }
                else if(i==4 || i==9 || i==15 || i==20 || i==26 || i==31 || i==37 || i==42 || i==48 || i==53 || i==59){
                    aux.at(i).Xcoord = 47.4f; }
                else if(i==5 || i==16 || i==27 || i==38 || i==49 || i==60){
                    aux.at(i).Xcoord = 52.2f; }
                else{
                    aux.at(i).Xcoord = 56.1f; }
            }
            //CONNECTIONS
            aux2.at(0).push_back(2); aux2.at(0).push_back(8); aux2.at(1).push_back(1); aux2.at(1).push_back(3);
            aux2.at(2).push_back(2); aux2.at(2).push_back(4); aux2.at(2).push_back(9); aux2.at(3).push_back(3);
            aux2.at(3).push_back(5); aux2.at(4).push_back(4); aux2.at(4).push_back(6); aux2.at(4).push_back(10);
            aux2.at(5).push_back(5); aux2.at(5).push_back(7); aux2.at(6).push_back(6); aux2.at(6).push_back(11);
            //
            aux2.at(7).push_back(1); aux2.at(7).push_back(12); aux2.at(8).push_back(3); aux2.at(8).push_back(14);
            aux2.at(9).push_back(5); aux2.at(9).push_back(16); aux2.at(10).push_back(7); aux2.at(10).push_back(18);
            aux2.at(11).push_back(8); aux2.at(11).push_back(13); aux2.at(11).push_back(19); 
            //
            aux2.at(12).push_back(12); aux2.at(12).push_back(14); aux2.at(13).push_back(9); aux2.at(13).push_back(13);
            aux2.at(13).push_back(15); aux2.at(13).push_back(20); aux2.at(14).push_back(14); aux2.at(14).push_back(16);
            aux2.at(15).push_back(10); aux2.at(15).push_back(15); aux2.at(15).push_back(17); aux2.at(15).push_back(21);
            aux2.at(16).push_back(16); aux2.at(16).push_back(18); aux2.at(17).push_back(11); aux2.at(17).push_back(17);
            aux2.at(17).push_back(22);
            //
            aux2.at(18).push_back(12); aux2.at(18).push_back(23); aux2.at(19).push_back(14); aux2.at(19).push_back(25);
            aux2.at(20).push_back(16); aux2.at(20).push_back(27); aux2.at(21).push_back(18); aux2.at(21).push_back(29);
            //
            aux2.at(22).push_back(19); aux2.at(22).push_back(24); aux2.at(22).push_back(30); aux2.at(23).push_back(23);
            aux2.at(23).push_back(25); aux2.at(24).push_back(20); aux2.at(24).push_back(24); aux2.at(24).push_back(26);
            aux2.at(24).push_back(31); aux2.at(25).push_back(25); aux2.at(25).push_back(27); aux2.at(26).push_back(21);
            aux2.at(26).push_back(26); aux2.at(26).push_back(28); aux2.at(26).push_back(32); aux2.at(27).push_back(27);
            aux2.at(27).push_back(29); aux2.at(28).push_back(22); aux2.at(28).push_back(28); aux2.at(28).push_back(33);
            //
            aux2.at(29).push_back(23); aux2.at(29).push_back(34); aux2.at(30).push_back(25); aux2.at(30).push_back(36);
            aux2.at(31).push_back(27); aux2.at(31).push_back(38); aux2.at(32).push_back(29); aux2.at(32).push_back(40);
            //
            aux2.at(33).push_back(30); aux2.at(33).push_back(35); aux2.at(33).push_back(41); aux2.at(34).push_back(34);
            aux2.at(34).push_back(36); aux2.at(35).push_back(31); aux2.at(35).push_back(35); aux2.at(35).push_back(37);
            aux2.at(35).push_back(42); aux2.at(36).push_back(36); aux2.at(36).push_back(38); aux2.at(37).push_back(32);
            aux2.at(37).push_back(37); aux2.at(37).push_back(39); aux2.at(37).push_back(43); aux2.at(38).push_back(38);
            aux2.at(38).push_back(40); aux2.at(39).push_back(33); aux2.at(39).push_back(39); aux2.at(39).push_back(44);
            //
            aux2.at(40).push_back(34); aux2.at(40).push_back(45); aux2.at(41).push_back(36); aux2.at(41).push_back(47);
            aux2.at(42).push_back(38); aux2.at(42).push_back(49); aux2.at(43).push_back(40); aux2.at(43).push_back(51);
            //
            aux2.at(44).push_back(41); aux2.at(44).push_back(46); aux2.at(44).push_back(52); aux2.at(45).push_back(45);
            aux2.at(45).push_back(47); aux2.at(46).push_back(42); aux2.at(46).push_back(46); aux2.at(46).push_back(48);
            aux2.at(46).push_back(53); aux2.at(47).push_back(47); aux2.at(47).push_back(49); aux2.at(48).push_back(43);
            aux2.at(48).push_back(48); aux2.at(48).push_back(50); aux2.at(48).push_back(54); aux2.at(49).push_back(49);
            aux2.at(49).push_back(51); aux2.at(50).push_back(44); aux2.at(50).push_back(50); aux2.at(50).push_back(55);
            //
            aux2.at(51).push_back(45); aux2.at(51).push_back(56); aux2.at(52).push_back(47); aux2.at(52).push_back(58);
            aux2.at(53).push_back(49); aux2.at(53).push_back(60); aux2.at(54).push_back(51); aux2.at(54).push_back(62);
            //
            aux2.at(55).push_back(52); aux2.at(55).push_back(57); aux2.at(56).push_back(56); aux2.at(56).push_back(58);
            aux2.at(57).push_back(53); aux2.at(57).push_back(57); aux2.at(57).push_back(59); aux2.at(58).push_back(58);
            aux2.at(58).push_back(60); aux2.at(59).push_back(54); aux2.at(59).push_back(58); aux2.at(59).push_back(60);
            aux2.at(60).push_back(59); aux2.at(60).push_back(61); aux2.at(61).push_back(55); aux2.at(61).push_back(61);

            waypointsLvl2.clear();

            for(int i=0; i<62;i++){
                aux.at(i).connectedWaypoints = aux2.at(i);
                waypointsLvl2.push_back(aux.at(i));
            }        

 //       break;
 //   }
}