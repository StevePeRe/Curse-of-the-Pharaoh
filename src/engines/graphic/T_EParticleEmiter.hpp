#pragma once

#include <engines/graphic/TEntity.hpp>
#include <engines/graphic/TNode.hpp>
#include <engines/graphic/Affector.hpp>

struct GraphicEngine;
struct TNodeTree;

// La luz hereda de Entity
struct T_EParticleEmiter : public TEntity
{
    T_EParticleEmiter(TNodeTree &tr) : treeNode{tr} {}

    void draw(GraphicEngine *ge, TNode *node);
    void updateParticles(GraphicEngine *ge, TNode *node);
    void update(GraphicEngine *ge, TNode::key_type id);
    void play();
    bool pushAffector(std::unique_ptr<Affector> affector_);

    // duracion de creacion de las particulas
    double duration{5};
    // el tiempo que viven las particulas
    double startLifeTime{5};
    // en forma de circulo spawn
    int spawnRadius{0};
    // si que se hace en el perimetro donde salen 
    bool perimeterSpawn{false};
    // seguir apareciendo particulas
    bool looping{false};
    // numero de particulas que crea por cada segundo
    double rateOverTime{5};
    // maximo de particulas
    size_t maxParticles{10};
    glm::vec3 color{0.0f,0.0f,0.0f};

private:
    std::vector<TNode::key_type> particles;
    std::vector<std::unique_ptr<Affector>> affectorList;
    TNodeTree& treeNode;
    double timer{0};
    double rateTimer{0};
    bool playing{true};
};