// raiz
#include <game/cmp/inventoryComponent.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
#include <game/man/event/eventManager.hpp>
// cmp
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/doorComponent.hpp>
#include <game/cmp/renderComponent.hpp>
// libs
#include <iostream>
// graphic
#include <engines/graphic/GraphicEngine.hpp>

void InventoryComponent::putIntoTheInventory(ECS::EntityManager &em, GraphicEngine &ge)
{
    std::size_t aux_id{0};
    auto &eventM = em.getSingletonComponentEM<EventManager>();
    auto *inv = em.getPlayer()->getComponent<InventoryComponent>();
    // recorre el mapa con los objetos que esten en el rango del jugador
    for (auto &par : inv->objectsInRange)
    {
        if (par.second && inv->collisionObject != ECS::EntityTAG::NO_TAG)
        {
            aux_id = par.first;
            eventM.addEventType(EventMask::PICK_OBJECT);
            addElement(inv->collisionObject);

            inv->objectsInRange[par.first] = false;
            inv->collisionObject = ECS::EntityTAG::NO_TAG;
            break;
        }
    }

    // BUSCA LA ENTIDAD CON ESE TIPO Y ESA ID PARA DESTRUIRLA
    for (auto &e : em)
    {
        // LO BUSCO PARA DESTRUIR
        if (e.getId() == aux_id)
        {
            ge.getNode(e.getComponent<RenderComponent>()->node)->setVisible(false);
            e.mark4destruction();
            em.destroy_marked_entities(); // necesario para poder borrar bien las entidades que ya no use en el inventario
            break;
        }
    }
}