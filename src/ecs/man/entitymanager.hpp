#pragma once
// cmp
#include <ecs/man/componentStorage.hpp>
#include <ecs/cmp/entity.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <vector>
#include <memory>
#include <cstdint>

namespace ECS
{
      struct EntityManager
      {

            explicit EntityManager();

            [[nodiscard]] Entity &newEntity() noexcept;

            // ------------------------------------------------------------------------------------
            // Singleton
            template <typename SingleCMP_Type>
            SingleCMP_Type &addSingletonComponent()
            {
                  auto &single_cmp = m_components.createSingletonComponent<SingleCMP_Type>();
                  return single_cmp;
            }

            template <typename SingleCMP_Type>
            SingleCMP_Type &getSingletonComponentEM()
            {
                  return m_components.getSingletonComponent<SingleCMP_Type>();
            }

            // ----------------------------------------------------------------------------
            // Component
            template <typename CMP_t>
            CMP_t &addComponent(Entity &e)
            {
                  auto &cmp = m_components.createComponent<CMP_t>(e.getId());
                  e.addComponent(cmp);
                  return cmp;
            }

            template <typename CMP_t>
            std::vector<CMP_t> &getComponents()
            {
                  return m_components.getComponents<CMP_t>();
            }

            const std::vector<Entity> &getEntityVector() const noexcept { return entities_; }
            std::vector<Entity> &getEntityVector() noexcept { return entities_; }

            const Entity *getEntityByID(std::size_t eid) const;
            Entity *getEntityByID(std::size_t eid);
            Entity *getEntityByType(ECS::EntityType type);
            Entity *getEntityByTAG(ECS::EntityTAG tag);

            Entity *getPlayer(){ return &entities_.at(0); }

            template <typename CMP_t>
            const std::vector<CMP_t> &getComponents() const
            {
                  return m_components.getComponents<CMP_t>();
            }

            void destroy_marked_entities();

            // actualziar las entidades
            void update()
            {
                  destroy_marked_entities();
                  incorporate_new_entities();
            }

            // recorrer el vector de componentes
            auto begin() noexcept { return entities_.begin(); }
            auto end() noexcept { return entities_.end(); }

            void cleanAll() noexcept
            {
                  alive_ = 0;
                  entities_.clear();
                  new_entities_.clear();
                  m_components.cleanAllComponents();
            }

      private:
            void incorporate_new_entities()
            {
                  for (auto &e : new_entities_)
                  {
                        entities_.push_back(std::move(e));
                  }
                  new_entities_.clear();
            }

            std::size_t alive_{};
            std::vector<Entity> entities_{}, new_entities_{};
            ComponentStorage m_components{MAX_ENTITIES};
      };

}