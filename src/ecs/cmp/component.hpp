#pragma once
// libs
#include <cstdint>

namespace ECS {

    struct Component
    {
        explicit Component(std::size_t eID)
            : entityID{ eID }
        {

        };

        virtual ~Component() = default;
        constexpr std::size_t getEntityID() const noexcept { return entityID; }

        private:
            std::size_t ComponentID { ++nextID };
            std::size_t entityID { 0 };

        inline static std::size_t nextID { 0 };
    };
    
    struct SingletonComponent
    {
        explicit SingletonComponent(std::size_t eID)
            : SingletonID{ eID }
        {
        };

        virtual ~SingletonComponent() = default;

        constexpr std::size_t getSingletonID() const noexcept { return SingletonID; }

        private:
            std::size_t SingletonID { 0 };
    };
}