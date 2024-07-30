#include <engines/graphic/GraphicEngine.hpp>
#include <game/sys/animation.hpp>
#include <ecs/man/entitymanager.hpp>
#include <game/cmp/animationComponent.hpp>
#include <game/cmp/physicsComponent.hpp>

#include <iostream>

bool AnimationSystem::update(ECS::EntityManager &em, [[maybe_unused]]GraphicEngine &ge, float dt)
{
    for (auto &animation : em.getComponents<AnimationComponent>())
    {
        if (animation.anim != nullptr)
            animation.anim->UpdateAnimation(dt);
    }
    return true;
}
