// managers
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/animationComponent.hpp>
#include <game/cmp/aiComponent.hpp>
#include "stbeh.hpp"
// libs
#include <cassert>
#include <ratio>
#include <thread>
#include <algorithm>
#include <numbers>
#include <cmath>
#include <vector>
// lib
#include <glm/glm.hpp>

Steer StBeh::idle(AIComponent& ai, PhysicsComponent& phy, AnimationComponent &anim_){
    // std::cout<< "idle" << std::endl;
    Steer st;
    auto current_time = std::chrono::steady_clock::now();

    if((current_time - last_idle_move) >= idle_move_wait && ai.tidlemov == false){ //cada idle_move_wait un nuevo target
        float distX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float distZ = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        int num = rand() % 10 + 1;
        if(num % 2 == 0){ distX *= -1; distZ *= -1;}

        ai.tidlex = phy.position.x + distX/4;
        ai.tidlez = phy.position.z + distZ/4;

        if(ai.tidlex < ai.idleRangeMinx || ai.tidlez < ai.idleRangeMinz){
            ai.tidlex = ai.idleRangeMinx;
            ai.tidlez = ai.idleRangeMinz;
        }
        else if(ai.tidlex > ai.idleRangeMaxx || ai.tidlez > ai.idleRangeMaxz){
            ai.tidlex = ai.idleRangeMaxx;
            ai.tidlez = ai.idleRangeMaxz;
        }

        last_idle_move = current_time;
        ai.tidlemov = true;
    }
    else if((std::abs(ai.tidlex-phy.position.x)>0.1f || std::abs(ai.tidlez-phy.position.z)>0.1f) && ai.tidlemov==true){
        st.linearVX = std::abs(ai.tidlex-phy.position.x)/ai.time2arrive;
        st.linearVZ = std::abs(ai.tidlez-phy.position.z)/ai.time2arrive;
        if(ai.tidlex<phy.position.x && st.linearVX>0){ st.linearVX = -st.linearVX; }
        if(ai.tidlez<phy.position.z && st.linearVZ>0){ st.linearVZ = -st.linearVZ; }
    }
    else if(std::abs(ai.tidlex-phy.position.x)<=0.1f && std::abs(ai.tidlez-phy.position.z)<=0.1f && ai.tidlemov==true){
        st.linearVX = 0.0f;
        st.linearVZ = 0.0f;
        ai.tidlemov = false;
    }

    // if (anim_.anim != nullptr)
    //     if (anim_.anim->checkEndAnimation() || anim_.anim->getCurrentAnimation() != anim_.idle)
    //             anim_.anim->setAnimation(anim_.idle);

    return st;
}

Steer StBeh::seek(AIComponent& ai, PhysicsComponent& phy, AnimationComponent &anim_){
    // std::cout<< "seek sbeh" << std::endl;
    float forceMagnitude = 5600.f; // fuerza con la que se mueve el personaje 
    Steer st;
    // if (!ai.tactive){ return st; }

    //linear distance to target
    auto dtx { ai.tx - phy.position.x };
    auto dtz { ai.tz - phy.position.z }; 

    //apply acceleration based on orientation
    auto acceleration { phy.maxALin /* / 1  */};
    st.linearVX = std::clamp( acceleration*dtx/ai.time2arrive, -phy.velLinearMax, phy.velLinearMax );
    st.linearVZ = std::clamp( acceleration*dtz/ai.time2arrive, -phy.velLinearMax, phy.velLinearMax );
    if(ai.tx<phy.position.x && st.linearVX>0){ -st.linearVX; }
    if(ai.tz<phy.position.z && st.linearVZ>0){ -st.linearVZ; }
    if(ai.tx>phy.position.x && st.linearVX<0){ -st.linearVX; }
    if(ai.tz>phy.position.z && st.linearVZ<0){ -st.linearVZ; }

    // std::cout << "x: " << st.linearVX << " , z: " << st.linearVZ << "\n";
    // if (anim_.anim != nullptr)
    //     if (anim_.anim->checkEndAnimation() || anim_.anim->getCurrentAnimation() != anim_.walk)
    //             anim_.anim->setAnimation(anim_.walk);

    return st;
}

Steer StBeh::arrive(AIComponent& ai, PhysicsComponent& phy){
    Steer st;
    // if (!ai.tactive){ return st; }
    phy.velAng = phy.ownForces.x = phy.ownForces.z = 0.0f;

    //linear distance to target
    auto dtx { std::abs(ai.tx - phy.position.x) };
    auto dtz { std::abs(ai.tz - phy.position.z) };

    st.linearVX = std::clamp( (dtx-phy.ownForces.x)*0.5f/(ai.time2arrive*ai.time2arrive), -phy.velLinearMax, phy.velLinearMax );
    st.linearVZ = std::clamp( (dtz-phy.ownForces.z)*0.5f/(ai.time2arrive*ai.time2arrive), -phy.velLinearMax, phy.velLinearMax );

    if(ai.tx<phy.position.x && st.linearVX>0){ st.linearVX = -st.linearVX; }
    if(ai.tz<phy.position.z && st.linearVZ>0){ st.linearVZ = -st.linearVZ; }
    if(ai.tx>phy.position.x && st.linearVX<0){ st.linearVX = -st.linearVX; }
    if(ai.tz>phy.position.z && st.linearVZ<0){ st.linearVZ = -st.linearVZ; }

    return st;
}

Steer StBeh::evade(AIComponent& ai, PhysicsComponent& phy, Steer& stprev, ECS::EntityManager& em){
    Steer st;
    bool closeEnemies = false;
    auto &iac = em.getComponents<AIComponent>();
    auto numIas = iac.size();

    for(int i=0; i<(int)numIas; i++){
        auto id = iac.at(i).getEntityID();
        auto ent1 = em.getEntityByID(id);
        auto phy2 = ent1->getComponent<PhysicsComponent>();

        if(std::abs(phy.position.x - phy2->position.x) <= ai.evadeRadius && std::abs(phy.position.z - phy2->position.z) <= ai.evadeRadius && id != ai.getEntityID()){
            auto vecEEx = phy.position.x - phy2->position.x;
            auto vecEEz = phy.position.z - phy2->position.z;

            closeEnemies = true;

            std::array<float, 2> vect = bisectriz(vecEEx/40.0f, vecEEz/40.0f, stprev.linearVX, stprev.linearVZ);

            st.linearVX = vect[0]/5;
            st.linearVZ = vect[1]/5;
        }
    }
    if(closeEnemies){    return st;   }
    else{     return stprev;    }
}

Steer StBeh::flock(AIComponent& ai, PhysicsComponent& phy, Steer& stprev, ECS::EntityManager& em){
    // std::cout << "FLOCK" << std::endl;
    Steer st;
    // bool closeEnemies = false;
    auto &iac = em.getComponents<AIComponent>();
    auto numIas = iac.size();
    int contador = 0;
    std::vector<PhysicsComponent> phys;

    for(int i=0; i<(int)numIas; i++){ 
        if(iac.at(i).enemyType == 2){ 
            contador++; 
            auto id = iac.at(i).getEntityID();
            auto ent1 = em.getEntityByID(id);
            auto phy2 = ent1->getComponent<PhysicsComponent>();
            phys.push_back(*phy2);
        }    
    }

    if(contador<2){   ai.behaviour = SB::Flee; return stprev;   }

    //std::array<float, 2> centro = centroid(phys);
    auto const [X, Z] = centroid(phys);
    float const radius = static_cast<float>(contador) * 0.5f * ai.flockRadius;
    // std::cout << "centroid: " << X << ", " << Z << std::endl;
    // std::cout << "flock radius: " << radius << std::endl;

    if(std::abs(phy.position.x - X) > radius || std::abs(phy.position.z - Z) > radius){
        // std::cout << "ESTAN FUERA DE RADIO" <<  std::endl;
        // std::cout << "dist x: " << std::abs(phy.position.x - X) << std::endl;
        // std::cout << "dist z: " << std::abs(phy.position.z - Z) << std::endl;
        auto vecECX = ((phy.position.x - X));
        auto vecECZ = ((phy.position.z - Z));

        if(std::abs(phy.position.x - X) > radius*2 || std::abs(phy.position.z - Z) > radius*2){
            st.linearVX = vecECX/(100);
            st.linearVZ = vecECZ/(100);
        }
        else{
            st.linearVX = vecECX/(100);
            st.linearVZ = vecECZ/(100);
        }

        if(X<phy.position.x && st.linearVX>0){ st.linearVX *= -1; }
        if(Z<phy.position.z && st.linearVZ>0){ st.linearVZ *= -1; }
        if(X>phy.position.x && st.linearVX<0){ st.linearVX *= -1; }
        if(Z>phy.position.z && st.linearVZ<0){ st.linearVZ *= -1; }

        return st;
    }
    else{
        // std::cout << "ESTAN DENTRO DE RADiO" << std::endl;
        return stprev;
    }    
}

Steer StBeh::flee(AIComponent& ai, PhysicsComponent& phy){
    Steer st;
    // if (!ai.tactive){ return st; }
    phy.velAng = phy.ownForces.x = phy.ownForces.z = 0.0f;

    //linear distance to target
    auto dtx { std::abs(ai.tx - phy.position.x) };
    auto dtz { std::abs(ai.tz - phy.position.z) };

    st.linearVX = std::clamp( (dtx-phy.ownForces.x)*0.5f/(ai.time2arrive*ai.time2arrive), -phy.velLinearMax, phy.velLinearMax );
    st.linearVZ = std::clamp( (dtz-phy.ownForces.z)*0.5f/(ai.time2arrive*ai.time2arrive), -phy.velLinearMax, phy.velLinearMax );

    if(ai.tx>phy.position.x && st.linearVX>0){ st.linearVX = -st.linearVX; }
    if(ai.tz>phy.position.z && st.linearVZ>0){ st.linearVZ = -st.linearVZ; }
    if(ai.tx<phy.position.x && st.linearVX<0){ st.linearVX = -st.linearVX; }
    if(ai.tz<phy.position.z && st.linearVZ<0){ st.linearVZ = -st.linearVZ; }

    return st;
}

std::array<float, 2> StBeh::centroid(const std::vector<PhysicsComponent>& points){
    float sumX = 0.0f, sumZ = 0.0f;
    for (int i=0; i<(int)points.size();i++){
        sumX += points.at(i).position.x;
        sumZ += points.at(i).position.z;
    }
    float centroidX = sumX/(float)(int)points.size();
    float centroidZ = sumZ/(float)(int)points.size();
    //std::array<float, 2> centroid;
    //centroid[0] = centroidX;
    //centroid[1] = centroidZ;
    //return centroid;
    return {centroidX, centroidZ};
}

float StBeh::angleBetweenVectors(float x1, float z1, float x2, float z2){
    float prod = x1 * x2 + z1 * z2;
    float mod1 = (float)sqrt(x1 * x1 + z1 * z1);
    float mod2 = (float)sqrt(x2 * x2 + z2 * z2);

    //proteccion contra divisiones entre cero
    if (mod1 == 0 || mod2 == 0) {
        return 0.0f;
    }

    float cos = prod / (mod1 * mod2);
    return acosf(cos);
}

std::array<float, 2> StBeh::bisectriz(float x1, float z1, float x2, float z2){
    Steer st;

    float angle = angleBetweenVectors(x1, z1, x2, z2);

    float halfAngle = angle / 2.0f;

    float cosHalfAngle = (float)cos(halfAngle);
    float sinHalfAngle = (float)sin(halfAngle);

    float bisX = x1 * cosHalfAngle + x2 * cosHalfAngle;
    float bisZ = z1 * sinHalfAngle + z2 * sinHalfAngle;

    std::array<float, 2> bis;
    bis[0] = bisX; bis[1] = bisZ; 

    return bis;
}

bool StBeh::perceptionBB(BlackBoardComponent& bb, AIComponent& ai, float dt){
    
    if(ai.enemyType!=2){ return false; } //solo escarabajos allowed
    ai.accumulatedDt += dt;
    if(ai.accumulatedDt <= ai.perceptionTime){ return false; }
    // std::cout << "perception BB, acc time: " << ai.accumulatedDt << std::endl;
    ai.accumulatedDt = 0.0f;

    if(bb.tactive){
        //escarabajos, cuando bb esta activo
        ai.tactive = bb.tactive;
        ai.tx = bb.tx;
        ai.tz = bb.tz;
    }
    return true;
}

bool StBeh::perception(AIComponent& ai, float dt){
    if(ai.enemyType==2){ return false; }
    ai.accumulatedDt += dt;
    if(ai.accumulatedDt <= ai.perceptionTime){ return false; }
    // std::cout << "perception, acc time: " << ai.accumulatedDt << std::endl;
    ai.accumulatedDt = 0.0f;
    return true;
}