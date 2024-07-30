#pragma once
// cmp
#include <ecs/cmp/component.hpp>
#include <game/cmp/aiComponent.hpp>
//util
#include <ecs/util/globals.hpp>
//libs
#include <cstdint>


struct BlackBoardComponent : ECS::SingletonComponent{ //para escarabajos
    float tx { 0.0f }, tz { 0.0f };
    bool tactive { false };

    /* float */

    explicit BlackBoardComponent() : ECS::SingletonComponent(ECS::IDSingleCMPBlackBoard){}

    // por ser singletonComponent
    static std::size_t getSingletonComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(ECS::IDSingleCMPBlackBoard);
    }
};


