#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// libs
////#include <raylib.h>
#include <cstdint>
#include <glm/glm.hpp>

struct RenderComponent : ECS::Component
{

    using key_type = std::size_t;

    explicit RenderComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(3);
    }

    float w{800}, h{600}, d{0}; // la d es depth
    float player_bend{0};
    float player_noBend{0};
    // float x{0}, y{0}, z{0}, velH{0};
    glm::vec3 color{1.0f,0.0f,0.0f};
    glm::vec3 damaged_color_reset{1.0f,0.0f,0.0f};
    /* glm::vec3 modelDirection{0.f}; */

    // borrar mensaje
    bool clearMessage{false};
    bool movableModel{true};

    key_type node;
    [[maybe_unnused]]key_type emisor;
};
