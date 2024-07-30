// raiz
#include <game/sys/collision.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
#include <game/man/event/eventManager.hpp>
#include <game/man/puzzlemanager.hpp>
// cmp
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/colliderComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
#include <game/cmp/inputComponent.hpp>
#include <game/cmp/cameraComponent.hpp>
#include <game/cmp/doorComponent.hpp>
#include <game/cmp/elevatorComponent.hpp>
#include <game/cmp/puzzleComponent.hpp>
#include <game/cmp/HUD/HUDComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/audioComponent.hpp>
#include <game/cmp/powerUpComponent.hpp>
#include <game/cmp/cinematicComponent.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// events
// triggers
#include <game/events/ArrowTrap.hpp>
// puzzle
#include <game/puzzles/puzzlePilares.hpp>
// util
#include <game/util/LayerMask.hpp>
// libs
#include <cstdint>
#include <iostream>

// TODO: para mucho mas adelante, que solo verifique las fisicas que estan alrededor del personaje dentor de un rango, optimizacion

void CollisionSystem::update(ECS::EntityManager &em)
{
    auto &bodies = em.getComponents<bodyComponent>();

    // segundo for de colision, entidades dynamicas con demas objetos estaticos, dinamicos y kinematicos
    for (std::size_t i = 0; i < bodies.size(); i++)
    {
        auto &bodyA = bodies[i];
        if (!bodyA.canCollide)
            continue;
        auto *e_bodyA = em.getEntityByID(bodyA.getEntityID());
        if (!e_bodyA)
            continue;
        auto *phyA = e_bodyA->getComponent<PhysicsComponent>();
        for (std::size_t j = i + 1; j < bodies.size(); j++)
        {
            auto &bodyB = bodies[j];
            if (!bodyB.canCollide)
                continue;
            auto *e_bodyB = em.getEntityByID(bodyB.getEntityID());
            if (!e_bodyB)
                continue;
            auto *phyB = e_bodyB->getComponent<PhysicsComponent>();
            if (phyB && phyA)
            {
                if ((phyA->static_ && phyB->static_) || (phyA->kinematic_ && phyB->kinematic_))
                    continue;

                if(e_bodyA->getType() != ECS::EntityType::PLAYER) {
                    if (bodyA.collisionAABB.checkObjectCollision(bodyA, bodyB, *phyA, *phyB))
                    {
                        solveCollision(em, *e_bodyA, *e_bodyB, *phyA, *phyB); // check colisiones de todos los demas interactuables
                    }
                } else {
                    if(bodyA.collisionAABB.checkObjectCollision(bodyA, bodyB, *phyA, *phyB)) {
                        solveCollisionPlayer(em, *e_bodyB, *phyB);            // check colisiones de solo el Player
                    } else
                    {
                        solveNoCollisionPlayer(em, *e_bodyB);
                    }
                }
            }
        }
    }

    // poner otro que solo cehckee la IA con el player
}

void CollisionSystem::solveCollisionPlayer(ECS::EntityManager &em, ECS::Entity &ent2, PhysicsComponent &phy2)
{
    
    auto *player = em.getPlayer();
    if (!player)
        return;

    if(player == &(ent2)) return;

    [[maybe_unused]] auto *heath1 = player->getComponent<HealthComponent>();
    auto *inv1 = player->getComponent<InventoryComponent>();
    auto *audio = player->getComponent<AudioComponent>();
    auto *power = player->getComponent<PowerUpComponent>();

    auto &eventM = em.getSingletonComponentEM<EventManager>();
    auto &puzzlM = em.getSingletonComponentEM<PuzzleManager>();
    auto &cinematicC = em.getSingletonComponentEM<CinematicComponent>();

    // END OF LEVEL
    if (ent2.getType() == ECS::EntityType::END_LEVEL)
    {
        // End level?
        eventM.addEventType(EventMask::LOAD_LEVEL);
    }

    // TRIGGERS
    if (phy2.triggerCollision && power) //  TMB PUEDE COLISIONAR EL PHY1 ser trigger, para todos los demas no jugadores
    {
        switch (ent2.getTAG())
        {
        case ECS::EntityTAG::INMUNITY:
            /* eventM.newTriggerEvent(InmunityPowerUp{false, 0.f}); */ // cerar otros triggers porque para powerUps mejor hacerlo a parte
            power->layer.AddLayer(PowerUps::INMUNITY_MODE);            //  activo el powerup
            eventM.addEventType(EventMask::POWER_UP_MUSIC);
            ent2.mark4destruction();
            break;
        case ECS::EntityTAG::SHOTGUNMODE:
            /* eventM.newTriggerEvent(ShotGunPowerUp{false, 0.f}); */
            power->layer.AddLayer(PowerUps::SHOTGUN_MODE); //  activo el powerup
            eventM.addEventType(EventMask::POWER_UP_MUSIC);
            ent2.mark4destruction();
            break;
        case ECS::EntityTAG::CHANGEm_DUNGEON:
            /* std::cout << "colisionao trigger music dungeon\n"; */
            eventM.addEventType(EventMask::DUNGEON_MUSIC);
            /* ent2.mark4destruction(); */
            break;
        case ECS::EntityTAG::CHANGEm_EXTERIOR:
            /* std::cout << "colisionao trigger music exterior\n"; */
            eventM.addEventType(EventMask::EXTERIOR_MUSIC);
            /* ent2.mark4destruction(); */
            break;
        default:
            break;
        }
        /* else if(ent2.getType() == ECS::EntityType::TRAP){

           eventM.newTriggerEvent(ArrowTrapEvent{false, 0.f}); // cuando colisione lanzo las flechas guardadas en el pool

       } */
    }

    if (ent2.getType() == ECS::EntityType::PROJECTILE)
    {
        if (heath1)
        {
            heath1->damaged = heath1->initInmunity = true;
            heath1->damage = ent2.getComponent<ShotBehaviourComponent>()->shot_damage;
            // std::cout << "health: " << heath1->health << std::endl;
        }
        ent2.mark4destruction();
    }

    // ////////////////////////

    // PUZZLE
    // colisionara con la entidad que sera la hitbox
    if (ent2.getType() == ECS::EntityType::PUZZLE_1)
    {
        auto *p_pilar = puzzlM.getPuzzle(ECS::PUZZLE_TYPE::PILARES);
        if (p_pilar)
        {
            /* std::cout << "entro colisiono bloque1\n"; */
            p_pilar->setIsActive(true);
        }
    }

    if (ent2.getType() == ECS::EntityType::PUZZLE_2)
    {
        auto *p_botones = puzzlM.getPuzzle(ECS::PUZZLE_TYPE::BOTONES);
        if (p_botones)
        {
            p_botones->setIsActive(true);
        }
    }

    // /////////////////////////////////////////////////////////////////
    // INVENTARIO
    if (inv1)
    {
        // colision objetos para inventario
        // cualquier objeto nuevo que se meta tiene que anyadirse aqui
        if(ent2.getType() == ECS::EntityType::PICKABLE_OBJECT) {
            inv1->collisionObject = ent2.getTAG();
            inv1->objectsInRange[ent2.getId()] = true;
        }
    }

    if (ent2.getType() == ECS::EntityType::CAMERA && CameraComponent::currentCam != ECS::ID_MOVABLE_CAM)
    {
        ent2.getComponent<CameraComponent>()->changeCurrentCam();

        cinematicC.idLastCam = ent2.getComponent<CameraComponent>()->idCam;
        CameraComponent::lastCam = ent2.getComponent<CameraComponent>()->idCam;
        // cambair a last cam
    }

    if (ent2.getType() == ECS::EntityType::SUELO_MUERTE)
    {
        if (audio)
            audio->play("DIE_JESS");
        player->mark4destruction();
    }
}

void CollisionSystem::solveNoCollisionPlayer(ECS::EntityManager &em, ECS::Entity &ent2)
{
    auto *player = em.getPlayer();
    if (!player)
        return;

    auto &puzzlM = em.getSingletonComponentEM<PuzzleManager>();
    auto *inv1 = player->getComponent<InventoryComponent>();

    // ////////////////////////////////////////////
    // INVENTARIO
    if (inv1)
    {
        for (auto &par : inv1->objectsInRange)
        {
            if (ent2.getId() == par.first)
            {
                inv1->objectsInRange[par.first] = false; // DEJO DE COLISIONAR
            }
        }
    }

    // ////////////////////////////////////////////
    // PUZZLE
    if (ent2.getType() == ECS::EntityType::PUZZLE_1)
    {
        auto *p_pilar = puzzlM.getPuzzle(ECS::PUZZLE_TYPE::PILARES);
        if (p_pilar)
        {
            p_pilar->setIsActive(false);
        }
    }

    if (ent2.getType() == ECS::EntityType::PUZZLE_2)
    {
        auto *p_botones = puzzlM.getPuzzle(ECS::PUZZLE_TYPE::BOTONES);
        if (p_botones)
        {
            p_botones->setIsActive(false);
        }
    }
}

void CollisionSystem::solveCollision([[maybe_unused]] ECS::EntityManager &em, ECS::Entity &ent1, ECS::Entity &ent2, [[maybe_unused]] PhysicsComponent &phy1, [[maybe_unused]] PhysicsComponent &phy2)
{
    /* auto *phyEnt1 = ent1.getComponent<PhysicsComponent>();
    auto *phyEnt2 = ent2.getComponent<PhysicsComponent>(); */
    auto *heath1 = ent1.getComponent<HealthComponent>();
    // auto *inv1 = ent1.getComponent<InventoryComponent>();
    // /* if(!phyEnt1 || !phyEnt2) return false; */

    // // pasrle los managers al constrcutor ua qye trabajan con ellas
    auto &eventM = em.getSingletonComponentEM<EventManager>();
    // auto &puzzlM = em.getSingletonComponentEM<PuzzleManager>();

    switch (ent1.getType())
    {
    // ----------------------------------------------------------------
    case ECS::EntityType::ENEMY:
        if (ent2.getType() == ECS::EntityType::BULLET)
        {
            if (heath1)
            {
                heath1->damaged = true;
                heath1->damage = ent2.getComponent<ShotBehaviourComponent>()->shot_damage;
            }
            ent2.mark4destruction();
        }

        if (ent2.getType() == ECS::EntityType::SUELO_MUERTE)
        {
            ent1.mark4destruction();
        }
        break;
    // ----------------------------------------------------------------
    case ECS::EntityType::PARED:
        if (ent2.getType() == ECS::EntityType::BULLET)
        {
            ent2.mark4destruction();
        }
        break;
    // ----------------------------------------------------------------
    case ECS::EntityType::BOX:
        if (ent2.getType() == ECS::EntityType::BULLET)
        {
            ent2.mark4destruction();
        }
        break;
    // ----------------------------------------------------------------
    case ECS::EntityType::SUELO_MUERTE:
        if (ent2.getType() == ECS::EntityType::ENEMY)
        {
            ent2.mark4destruction();
        }
        break;
    // ----------------------------------------------------------------
    case ECS::EntityType::TRAP:
        ent1.getTAG();
        eventM.newTriggerEvent(ArrowTrapEvent{false, 0.f}); // cualquier otra entidad tmb puede activar las trampas o triggers que esten aqui

        break;
    }

    switch (ent2.getType())
    {
        // ----------------------------------------------------------------
    case ECS::EntityType::TRAP:
        eventM.newTriggerEvent(ArrowTrapEvent{false, 0.f}); // cualquier otra entidad tmb puede activar las trampas o triggers que esten aqui

        break;
    }
}

void CollisionSystem::solveNoCollision(ECS::EntityManager &, ECS::Entity &, ECS::Entity &)
{
}