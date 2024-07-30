// raiz
#include <game/sys/ai.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/aiComponent.hpp>
#include <game/ai/bt/behaviourtree.hpp>
// Graphic Engine
#include <engines/graphic/GraphicEngine.hpp>
// libs
#include <cassert>
#include <ratio>
#include <thread>
#include <algorithm>
#include <numbers>
#include <cmath>

void AISystem::update(ECS::EntityManager &em, GraphicEngine& graphic, float deltaTime, GameObjectFactory &GOF){
    auto &iac = em.getComponents<AIComponent>();
    auto playerPhys = em.getPlayer()->getComponent<PhysicsComponent>();

    for (std::size_t i = 0; i < iac.size(); i++){
        const auto eptr = em.getEntityByID(iac.at(i).getEntityID());
        auto &e = *eptr;
        if(eptr && eptr->getComponent<PhysicsComponent>()){
            auto const &ai = e.getComponent<AIComponent>();
            auto const &phy = e.getComponent<PhysicsComponent>();

            float distancia = std::sqrt(((playerPhys->position.x - phy->position.x)*(playerPhys->position.x - phy->position.x)) 
                                      + ((playerPhys->position.y - phy->position.y)*(playerPhys->position.y - phy->position.y)) 
                                      + ((playerPhys->position.z - phy->position.z)*(playerPhys->position.z - phy->position.z)));
            
            if(distancia < 20.f && iac.at(i).behaviourTree != nullptr){ 
                ai->running = true;
                EntityContext ectx {*phy, e, em, GOF};
                ai->behaviourTree->run( ectx, deltaTime );
            }
            else{
                ai->running = false;
                ai->currentNode = 0;
            }
            ai->distPlayer = distancia;
        }
    }
}