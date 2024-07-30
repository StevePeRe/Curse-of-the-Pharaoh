#pragma once
// libs
#include <cstdlib>
#include <engines/graphic/SAnimator.hpp>
#include <glm/glm.hpp>

// #include <cstdint>

struct GLFWwindow;

namespace ECS
{
    struct EntityManager;
}

struct GraphicEngine;
struct GLFWwindow;

struct RenderSystem
{
    using key_type = std::size_t;

    explicit RenderSystem() = default;
    virtual ~RenderSystem();

    void init(GraphicEngine &ge);
    // Por ahora los 2 vectores mas importantes de la camara para luego crear el camara component
    void update(ECS::EntityManager &em, GraphicEngine &ge, float dt);
    void rotationModel(GraphicEngine &ge);
    void imGuiInit();

private:
    key_type camara;
    GLFWwindow* window {nullptr};
    bool controlHUD{true};
    key_type prueba;
    SAnimator* anim;

    float angle{0.f};
    float angleDegrees{0.f};
    glm::vec3 vecToRotate{0.f};
    glm::vec3 rotationVector;
    glm::mat4 viewMatrixPlayer{0.f};
};