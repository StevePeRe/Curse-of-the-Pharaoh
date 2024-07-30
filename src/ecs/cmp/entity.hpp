#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace ECS{

    struct Entity {

        explicit Entity() = default;

        template<typename CMP_t>
        void addComponent(CMP_t& cmp) {
            auto type = cmp.getComponentTypeID();
            m_components[type] = &cmp;
        }

        template<typename CMP_t>
        CMP_t* getComponent() {
            auto type = CMP_t::getComponentTypeID();
            auto it = m_components.find(type);
            if( it != m_components.end() ){
                return static_cast<CMP_t*>(it->second);
            }
            return nullptr;
        }

        template<typename CMP_t>
        const CMP_t* getComponent() const {
            auto* p = const_cast<Entity*>(this)->getComponent<CMP_t>();
            return const_cast<const Component*>(p);
        }

        // Id de la entidad
        constexpr std::size_t getId() const noexcept  { return Id; } 

        void mark4destruction(){ alive = false; }
        bool getIsAlive(){ return alive; }
        
        // tipo de entidad y estado
        void setType(EntityType tp){ this->type = tp; }
        char getType(){ return this->type; }

        void setState(EntityState state){ this->entState = state; }
        char getState(){ return this->entState; }

        void setTAG(EntityTAG tag){ this->entTag = tag; }
        EntityTAG getTAG(){ return this->entTag; }

        // para recorrer en el EM los componentes
        auto begin() { return m_components.begin(); }
        auto end()   { return m_components.end(); }

        // cuando eliminamos un componente actualizamos la entidad para que apunte a su nuevo sitio
        void updateComponent(std::size_t cmpID, Component* cmpptr){
            auto it = m_components.find(cmpID);
            if(it != m_components.end()){
                it->second = cmpptr; 
            }
        }

        private:
        std::unordered_map<std::size_t, Component*> m_components;
        std::size_t Id{ ++nextID };//pertenece a la entidad
        inline static std::size_t nextID { 0 };

        // alive or not
        bool alive { true };
        EntityType type { EntityType::NONE };
        EntityState entState { EntityState::IDLE };
        EntityTAG entTag { EntityTAG::NO_TAG };
    };

}