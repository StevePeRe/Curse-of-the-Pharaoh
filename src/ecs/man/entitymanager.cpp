// raiz
#include <ecs/man/entitymanager.hpp>
// libs
#include <cassert>
#include <iostream>
#include <cstdint>

namespace ECS
{
    EntityManager::EntityManager()
    {
        entities_.reserve(MAX_ENTITIES);
    }
    ////////////////////////////////////////////////////////////////
    [[nodiscard]] Entity &EntityManager::newEntity() noexcept
    {
        assert(alive_ < MAX_ENTITIES);

        alive_ += 1;
        Entity &e = entities_.emplace_back();
        return e;
    }
    /////////////////////////////////////////////////////////////////////////////////////
    const Entity *EntityManager::getEntityByID(std::size_t eid) const
    {
        for (size_t i = 0; i < entities_.size(); i++)
        {
            if (entities_.at(i).getId() == eid)
            {
                return &entities_[i];
            }
        }
        return nullptr;

    }

    /////////////////////////////////////////////////////////////////////////////////////
    Entity *EntityManager::getEntityByID(std::size_t eid)
    {
        auto eptr = const_cast<const EntityManager *>(this)->getEntityByID(eid);
        return const_cast<Entity *>(eptr);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    Entity *EntityManager::getEntityByType(ECS::EntityType type) {
        // la primera entidad con el tipo pasado la devuelve
        for (size_t i = 0; i < entities_.size(); i++)
        {
            if (entities_.at(i).getType() == type)
            {
                return &entities_[i];
            }
        }
        return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // hecho ya que habran entidades con el mismo tipo, pero distinto tag para diferenciarlas
    Entity *EntityManager::getEntityByTAG(ECS::EntityTAG tag) {
        // la primera entidad con el tag pasado la devuelve
        for (size_t i = 0; i < entities_.size(); i++)
        {
            if (entities_.at(i).getTAG() & tag)
            {
                return &entities_[i];
            }
        }
        return nullptr;
    }

    void EntityManager::destroy_marked_entities()
    {
        for (auto iplus1{entities_.size()}; iplus1 != 0; iplus1--)
        {
            auto i = iplus1 - 1;
            auto &e = entities_[i];
            if (!(e.getIsAlive()))
            {
                // destruyo sus componentes y actualiazo la entidad que estaba apuntando a ellos
                for (auto &[typeID, _] : e)
                {
                    auto *cmpptr = m_components.deleteCmpByTypeIDAndEntityID(typeID, e.getId());
                    if (!cmpptr)
                        continue;
                    auto *movedEntity{getEntityByID(cmpptr->getEntityID())};
                    if (cmpptr != nullptr && movedEntity != nullptr)
                    {
                        movedEntity->updateComponent(typeID, cmpptr);
                    }
                }
                entities_.erase(entities_.begin() + long(i));
                alive_ -= 1;
            }
        }
    }
}