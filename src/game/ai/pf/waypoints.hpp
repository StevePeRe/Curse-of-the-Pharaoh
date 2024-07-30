#pragma once
#include <vector>
#include <math.h>

struct Waypoint {

    float getF() { return G + H; }

    //float getH(Waypoint &nodeEnd){ //distancia desde aqui hasta el nodo final
    //    float x = fabs(this->Xcoord - nodeEnd.Xcoord);
    //    float y = fabs(this->Zcoord - nodeEnd.Zcoord);
    //    return (x + y);
    //}

    //float getG(Waypoint &nodeStart){ //distancia desde el nodo comienzo hasta aqui
    //    float x = fabs(nodeStart.Xcoord - this->Xcoord);
    //    float y = fabs(nodeStart.Zcoord - this->Zcoord);
    //    return (x + y);
    //}

    std::size_t id{ ++nextID };
    inline static std::size_t nextID { 0 };

    float Xcoord { 0.0f };
    float Zcoord { 0.0f };

    int idPrev {0};  //id del wp previo en el path. 0->no tiene prev // -1 -> start cell
    std::vector<int> connectedWaypoints;

    bool visited { false };
    bool recorded { false };

    float G { 0.0f };
    float H { 0.0f }; //heuristic -> distancia hasta el objetivo
};
  