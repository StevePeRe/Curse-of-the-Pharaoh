#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// libs
#include <unordered_map>
#include <optional>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>

// ---------------------------------------------------------
//  GUIA TypeIds COMPONENTES: (para no repetir)
// ---------------------------------------------------------
//  1 ->    inventoryComponent
//  2 ->      physicsComponent
//  3 ->       renderComponent
//  4 ->       cameraComponent
//  5 ->ShotBehaviourComponent
//  6 ->     colliderComponent
//  7 ->  autodestroyComponent
//  8 ->        inputComponent
//  9 ->         doorComponent
// 10 ->           aiComponent
// 11 ->       healthComponent
// 12 ->    pathComponent
// 13 ->    bodyComponent
// 14 ->    worldComponent
// 15 ->    spawnerComponent
// 16 ->    puzzleComponent
// 17 ->    messageComponent
// 18 ->    elevatorComponent
// 19 ->    audioComponent
// 20 ->    switchComponent
// 21 ->    raycastComponent
// 22 ->    animationComponent
//----------------------------------------------------------
// ---------------------------------------------------------
//  GUIA TypeIds SINGLETON-COMPONENTES: (para no repetir) mejor que no hayan muchos
// ---------------------------------------------------------
//  1 ->    EventManager
//  2 ->    BlackBoard  
//  3 ->       
//  4 ->       
//----------------------------------------------------------


namespace ECS{

        struct ComponentVectorBase{
            virtual ~ComponentVectorBase() = default;
            virtual Component* deleteCmpByEntityID(std::size_t eID) = 0;
        };

        template <typename CMP_t>
        // clase template
        struct ComponentVector : ComponentVectorBase
        {
            // vector de componentes de cada tipo de componente
            std::vector<CMP_t> components;
            constexpr auto findCmpIteratorByID(std::size_t eID) noexcept {
                std::optional itopt = 
                    std::find_if(components.begin(), components.end(),
                    [&eID](CMP_t& cmp) { return cmp.getEntityID() == eID; }
                    );
                if(*itopt == components.end()) itopt.reset();
                return itopt;
            }

            Component* deleteCmpByEntityID(std::size_t eID) override final {
                auto itopt = findCmpIteratorByID(eID);
                if(!itopt) return nullptr;  

                auto it = *itopt;
                if(it + 1 != components.end())
                    *it = components.back();
                components.pop_back();

                return it.base();
            }
        };
        

    struct ComponentStorage {
        ComponentStorage() = delete;
        explicit ComponentStorage(std::size_t _initialize) 
            : m_initialSize(_initialize)
        {
        };

        // OPERADORES ASIGNACION
        ComponentStorage(const ComponentStorage& ) = delete;
        ComponentStorage(ComponentStorage&&) = delete;
        ComponentStorage& operator=(const ComponentStorage& ) = delete;
        ComponentStorage& operator=(ComponentStorage&&) = delete;

        // TEMPLATE
        // crea el vector de componentes que queramos
        template <typename CMP_t>
        std::vector<CMP_t>& createComponentVector(){
            auto typeID = CMP_t::getComponentTypeID();
            auto v = std::make_unique<ComponentVector<CMP_t>>();
            v->components.reserve(m_initialSize);
            // son punteros usuario
            auto* vecptr = v.get();
            m_components_v[typeID] = std::move(v);
            return vecptr->components;

        }

        // obtener vector de componentes 
        template <typename CMP_t>
        std::vector<CMP_t>& getComponents(){
            std::vector<CMP_t>* comvec{ nullptr };
            auto typeID = CMP_t::getComponentTypeID();
            auto it = m_components_v.find(typeID);
            if( it != m_components_v.end() ){
                auto *v = dynamic_cast<ComponentVector<CMP_t>*>(it->second.get());
                comvec = &(v->components);
            }else{
                comvec = &createComponentVector<CMP_t>();
            }
            return *comvec;
        }

        // obtener vector de componentes const
        template <typename CMP_t>
        const std::vector<CMP_t>& getComponents() const {
            std::vector<CMP_t>* comvec{ nullptr };
            auto typeID = CMP_t::getComponentTypeID();
            auto it = m_components_v.find(typeID);
            if( it != m_components_v.end() ){
                auto *v = static_cast<ComponentVector<CMP_t>*>(it->second.get());
                comvec = &(v->components);
            }else{
                throw "NO existe ComponentVector!!";
            }
            return *comvec;
        }

        // crear componente - le paso la ID de la entidad dueña
        template <typename CMP_t>
        CMP_t& createComponent(std::size_t eID){
            auto& v = getComponents<CMP_t>();
            // le devuelve todo el vector si existe e inicializa un nuevo valor
            auto& cmp = v.emplace_back(eID);
            return cmp;
        }

        // con el ID del cmp, lo busco en el vector, para luego borrarlo desde el hijo
        Component* deleteCmpByTypeIDAndEntityID(std::size_t cmpID, std::size_t entityID){
            auto it = m_components_v.find(cmpID);
            if(it == m_components_v.end()) return nullptr;
            return it->second->deleteCmpByEntityID(entityID);
        }

        // ///////////////////////////////////////////////////////////////////////////////////
        // Manage of Singleton Components
        // Devuelve y Crea SingletonComponents
        template <typename SingletonCMP>
        SingletonCMP& createSingletonComponent(){
            SingletonCMP *singleCMP { nullptr };
            auto typeID = SingletonCMP::getSingletonComponentTypeID();
            auto it = m_singletonComponents_v.find(typeID);
            if(it != m_singletonComponents_v.end()) {
                singleCMP = static_cast<SingletonCMP *>(it->second.get());
            }else{
                m_singletonComponents_v.emplace(typeID, std::make_unique<SingletonCMP>());
                singleCMP = static_cast<SingletonCMP *>(m_singletonComponents_v[typeID].get());
            }

            if(singleCMP == nullptr){
                std::cout << "\nERRROR NULLLLLL " << typeID << "\n";
            }

            return *singleCMP;
        }

        // Devuelve SingletonCMP
        template <typename SingletonCMP>
        SingletonCMP& getSingletonComponent(){

            SingletonCMP *singleCMP { nullptr };
            auto typeID = SingletonCMP::getSingletonComponentTypeID();
            auto it = m_singletonComponents_v.find(typeID);

            if(it != m_singletonComponents_v.end()) {
                singleCMP = static_cast<SingletonCMP *>(it->second.get());
            }
            return *singleCMP;
        }

        void cleanAllComponents(){
            m_components_v.clear();
            m_singletonComponents_v.clear();
        }

    private:
        std::unordered_map<std::size_t, std::unique_ptr<ComponentVectorBase>> m_components_v{};
        std::unordered_map<std::size_t, std::unique_ptr<SingletonComponent>> m_singletonComponents_v{};
        std::size_t m_initialSize{ 100 };
   
    };

} 