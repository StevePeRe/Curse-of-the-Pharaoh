#include <game/sys/inventory.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
#include <game/cmp/doorComponent.hpp>
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/inputComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/HUD/HUDComponent.hpp>
#include <game/cmp/audioComponent.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// libs
//#include <raylib.h>
#include <iostream>
// Graphic
/* #include <engines/graphic/GraphicEngine.hpp> */

void InventorySys::update(ECS::EntityManager &em)
{
    auto *player = em.getPlayer();
    auto &HUD = em.getSingletonComponentEM<HUDComponent>();

    if (player)
    {
        auto *inv = player->getComponent<InventoryComponent>();
        auto *inp = player->getComponent<InputComponent>();
        auto *beh = player->getComponent<ShotBehaviourComponent>();
        
        if (inv && inp && beh)
        {
            if (inp->useInventory)
            {
                switchObjects(em, *player, inv->getObjectInHand().first);
            }

            if (inp->interaction)
            {
                auto *e = doorCollision(em);
                // saber si colisiono con una puerta
                if (e)
                {
                    auto *aud = e->getComponent<AudioComponent>();
                    if(!inv->hasKeys()){
                        if(aud && !(aud->getAudioInstance("DOOR_CLOSED")->GetState() == AudioInstance::AudioState::PLAYING))
                            aud->play("DOOR_CLOSED");

                        HUD.setQuickMessage("No tengo ninguna llave en mi inventario.");
                        HUD.showQuickMessage();
                    }else{
                        switch (inv->getObjectInHand().first)
                        {
                        // necesario para saber que llave tienes en mano para abrir la puerta
                        case ECS::EntityTAG::KEY_1:
                            openDoor(em, ECS::EntityTAG::KEY_1);
                            break;
                        case ECS::EntityTAG::KEY_2:
                            openDoor(em, ECS::EntityTAG::KEY_2);
                            break;
                        case ECS::EntityTAG::KEY_3:
                            openDoor(em, ECS::EntityTAG::KEY_3);
                            break;
                        case ECS::EntityTAG::KEY_4:
                            openDoor(em, ECS::EntityTAG::KEY_4);
                            break;
                        default:
                            if(aud && !(aud->getAudioInstance("DOOR_CLOSED")->GetState() == AudioInstance::AudioState::PLAYING))
                                aud->play("DOOR_CLOSED");   
                            HUD.setQuickMessage("Deberia revisar si tengo alguna llave para esta puerta.");
                            HUD.showQuickMessage();
                            break;
                        }
                    }
                }
            }

            if (inp->useAMMO && beh->shot_ammo != beh->shot_maxAmmo)
            {
                if (inv->hasObject(ECS::EntityTAG::AMMO))
                    switchObjects(em, *player, ECS::EntityTAG::AMMO);
            }
        }
    }
}

void InventorySys::switchObjects(ECS::EntityManager &em, ECS::Entity &player, ECS::EntityTAG tag)
{
    auto *beh = player.getComponent<ShotBehaviourComponent>();
    auto *hlt = player.getComponent<HealthComponent>();
    auto *inv = player.getComponent<InventoryComponent>();
    auto *aud = player.getComponent<AudioComponent>();

    if (beh && hlt && inv && aud)
    {
        switch (tag)
        {
        case ECS::EntityTAG::AMMO:
            if(beh->shot_ammo != beh->shot_maxAmmo) {
                beh->shot_ammo = 8;
                aud->play("RELOAD_JESS");
                inv->removeElement(ECS::EntityTAG::AMMO);
            }
            break;
        case ECS::EntityTAG::BIG_HEAL:
            if(hlt->health != 100){
                std::cout << "Curo 25\n";
                if (hlt->health + 25 > 100)
                {
                    hlt->health = 100;
                }
                else
                {
                    hlt->health += 25;
                }
                aud->play("HEAL2_JESS");
                inv->removeElement(ECS::EntityTAG::BIG_HEAL);
            }
            break;
        case ECS::EntityTAG::SMALL_HEAL:
            if(hlt->health != 100){
                std::cout << "Curo 10\n";
                if (hlt->health + 10 > 100)
                {
                    hlt->health = 100;
                }
                else
                {
                    hlt->health += 10;
                }
                aud->play("HEAL1_JESS");
                inv->removeElement(ECS::EntityTAG::SMALL_HEAL);
            }
            break;
        case ECS::EntityTAG::KEY_1:
            openDoor(em, ECS::EntityTAG::KEY_1);
            break;
        case ECS::EntityTAG::KEY_2:
            openDoor(em, ECS::EntityTAG::KEY_2);
            break;
        default:
            std::cout << "Ningun objeto para usar\n";
            break;
        }
    }
}

void InventorySys::openDoor(ECS::EntityManager &em, ECS::EntityTAG keyTag)
{
    auto &HUD = em.getSingletonComponentEM<HUDComponent>();
    auto *inv = em.getPlayer()->getComponent<InventoryComponent>();
    
    auto *e = doorCollision(em);
    if (e)
    {
        auto *doorAud  = e->getComponent<AudioComponent>();
        auto *doorC    = e->getComponent<DoorComponent>();

        if (doorC && doorC->keyTag == keyTag)
        {
            inv->removeElement(keyTag);
            doorAud->play("DOOR_OPEN");
            e->mark4destruction();
            /* std::cout << "abres la puerta\n"; */
        }else
        {
            // si no la puedo abrir con la llave que tengo
            // poner mensaje de lave incorrecta
            doorAud->play("DOOR_CLOSED");
            HUD.setQuickMessage("La llave parece incorrecta.");
            HUD.showQuickMessage();
        }
    }
}

ECS::Entity *InventorySys::doorCollision(ECS::EntityManager &em)
{
    ECS::Entity *ent_dev = nullptr;
    auto *bod = em.getPlayer()->getComponent<bodyComponent>();
    auto *phy = em.getPlayer()->getComponent<PhysicsComponent>();
    auto &doors = em.getComponents<DoorComponent>();

    auto &HUD = em.getSingletonComponentEM<HUDComponent>();

    for (auto &door : doors)
    {
        auto *e = em.getEntityByID(door.getEntityID());
        if (e)
        {
            auto *phyDoor  = e->getComponent<PhysicsComponent>();
            auto *bodyDoor = e->getComponent<bodyComponent>();
            auto *doorC    = e->getComponent<DoorComponent>();
            auto *doorAud  = e->getComponent<AudioComponent>();
            if (bod && phy && bodyDoor && phyDoor)
            {
                if (bod->collisionAABB.checkObjectCollision(*bod, *bodyDoor, *phy, *phyDoor))
                {
                    if(doorC->doorType == ECS::EntityType::DOOR_NO_KEY){ // habro la puerta que no requiere llave
                        HUD.setQuickMessage("La puerta parece no necesitar llave.");
                        HUD.showQuickMessage();
                        doorAud->play("DOOR_OPEN");
                        e->mark4destruction();
                        break;
                    }
                    // si colisiona con una puerta, devuelvo la puerta
                    ent_dev = e;
                    break;
                }
            }
        }
    }

    return ent_dev;
}