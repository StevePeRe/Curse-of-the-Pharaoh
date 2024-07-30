#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>

namespace ECS
{
    struct EntityManager;
}

struct GraphicEngine;

struct InventoryComponent : ECS::Component
{
    using ObjectHandType   = std::pair<ECS::EntityTAG, uint32_t>;
    using InventoryVecPair = std::vector<ObjectHandType>;
    
    // using ObjectsVector = std::vector<ECS::EntityType>;

    explicit InventoryComponent(std::size_t eID) : ECS::Component(eID)
    {
        inventoryData.reserve(100);
        // inventoryData.push_back(std::make_pair(ECS::EntityType::NO_OBJECT_HAND,0));
    };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(1);
    }

    void putIntoTheInventory(ECS::EntityManager &em, GraphicEngine &ge);

    void ApplyQuantity(ECS::EntityTAG object_type, int16_t quantity = 1){
        bool exist = false;
        for (int16_t i = 0; i < static_cast<int16_t>(inventoryData.size()); i++)
        {
            if (inventoryData[i].first == object_type)
            {
                exist = true; 
                // ya existe el objeto en el inventario
                if(inventoryData[i].second <= MAX_OBJECT_Q) // cantidad maximo de items
                    inventoryData[i].second = quantity;
                else inventoryData[i].second = MAX_OBJECT_Q; 

                index = i;
                objectInHand = inventoryData[i];
                break;
            }
        }
        if(!exist){
            inventoryData.push_back(std::make_pair(object_type, quantity));
            objectInHand = inventoryData.at(static_cast<int16_t>(inventoryData.size()) - 1);
            index = static_cast<int16_t>(inventoryData.size()) - 1;
        }
    }

    // el = 1, si no paso parametro se le asgina por defecto
    void addElement(ECS::EntityTAG object_type, int16_t quantity = 1)
    {
        bool exist = false;
        for (int16_t i = 0; i < static_cast<int16_t>(inventoryData.size()); i++)
        {
            if (inventoryData[i].first == object_type)
            {
                // ya existe el objeto en el inventario
                exist = true; 
                if(inventoryData[i].second + quantity < MAX_OBJECT_Q) // cantidad maximo de items
                    inventoryData[i].second += quantity;
                else inventoryData[i].second = MAX_OBJECT_Q; 

                index = i;
                // ponerle el index en la i
                objectInHand = inventoryData[i];
                break;
            }
        }

        if(!exist){
            inventoryData.push_back(std::make_pair(object_type, quantity));
            objectInHand = inventoryData.at(static_cast<int16_t>(inventoryData.size()) - 1);
            index = static_cast<int16_t>(inventoryData.size()) - 1;
        }
    }

    void removeElement(ECS::EntityTAG object_tag, int16_t quantity = 1)
    {
        for (int16_t i = 0; i < static_cast<int16_t>(inventoryData.size()); i++)
        {
            if (inventoryData[i].first == object_tag)
            {
                if(inventoryData[i].second > 1){
                    inventoryData[i].second -= quantity;
                    objectInHand = inventoryData[i];
                    break;
                } else{
                    inventoryData.erase(inventoryData.begin() + i);
                    if(inventoryData.size() > 0){
                        objectInHand = inventoryData.at(0);
                        index = 0;
                    }
                    break;
                }
            }
        }  
        if(inventoryData.size() <= 0){
            objectInHand.first = ECS::EntityTAG::NO_TAG;
        }

    }

    void eraseElement(ECS::EntityTAG object_tag) {
        for (int16_t i = 0; i < static_cast<int16_t>(inventoryData.size()); i++)
        {
            if (inventoryData[i].first == object_tag)
            {
                inventoryData.erase(inventoryData.begin() + i);
                if(inventoryData.size() > 0){
                    objectInHand = inventoryData[0];
                    index = 0;
                }
                break;
            }
        }  
        if(inventoryData.size() <= 0){
            objectInHand.first = ECS::EntityTAG::NO_TAG;
        }
    }

    // cambiara a -> usar objeto
    bool hasObject(ECS::EntityTAG object_tag)
    {
        bool exist = false;
        for (int16_t i = 0; i < static_cast<int16_t>(inventoryData.size()); i++)
        {
            if (inventoryData[i].first == object_tag)
            {
                // existe el objeto en el inventario
                exist = true; 
                break;
            }
        }

        return exist;
    }

    bool hasKeys()
    {
        bool exist = false;
        for (int16_t i = 0; i < static_cast<int16_t>(inventoryData.size()); i++)
        {
            if (inventoryData[i].first == ECS::EntityTAG::KEY_1 || inventoryData[i].first == ECS::EntityTAG::KEY_2 || 
                inventoryData[i].first == ECS::EntityTAG::KEY_3 || inventoryData[i].first == ECS::EntityTAG::KEY_4) {
                // existe la llave en el ivnentario
                exist = true; 
                break;
            }
        }

        return exist;
    }

    InventoryVecPair &getInventory()    { return inventoryData; }  

    ObjectHandType   &getObjectInHand() { return objectInHand; }
    void setObjectHand(ObjectHandType object) { objectInHand = object; }

    // std::size_t getKeyID() { return keyID; };

    // TODO+ fixear esto
    // std::pair<std::size_t, ECS::EntityType> objectInRange{0, ECS::EntityType::NONE};

    ECS::EntityTAG collisionObject;
    //               ID DE ENTIDAD, EN RANGO
    // podria ser un pair
    std::unordered_map<std::size_t, bool> objectsInRange{}; // MAPA DE OBEJTOS PARA COMPROBAR QUE ESTAN EN RANGO

    int16_t index{0}; // indice dle inventario

private:
    InventoryVecPair inventoryData{};
    ObjectHandType   objectInHand{ECS::EntityTAG::NO_TAG, 0};
    static constexpr int16_t MAX_OBJECT_Q{10};

    // std::size_t      keyID{0};
};
