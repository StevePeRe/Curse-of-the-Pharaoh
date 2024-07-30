#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <vector>
#include <cstdint>
#include <map>
// graphic
#include <engines/graphic/SAnimator.hpp>
#include <engines/graphic/RAnimation.hpp>

struct AnimationComponent : ECS::Component
{
    using AnimationContainer = std::map<std::string, RAnimation *>;

    explicit AnimationComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(22);
    }

    RAnimation *getAnimationByName(std::string animationName)
    {
        // auto it = animationList.find(animationName);
        auto anim = animationList[animationName];

        if (!anim)
        {
            return anim;
        }

        return nullptr;
    }

    void setAnimationByName(std::string animationName)
    {
        anim->setAnimation(getAnimationByName(animationName));
    }

    AnimationContainer &getAnimationList() { return animationList; }

    SAnimator *getAnimator() { return anim; }
    void setAnimator(SAnimator *animator) { anim = animator; }

    // hay que cambiar esto cuanto antes
    SAnimator *anim{};
    [[maybe_unnused]]AnimationContainer animationList{};
    [[maybe_unnused]]RAnimation* idle{nullptr};
    [[maybe_unnused]]RAnimation* walk{nullptr};
    [[maybe_unnused]]RAnimation* crouch{nullptr};
    [[maybe_unnused]]RAnimation* crouchWalk{nullptr};
    [[maybe_unnused]]RAnimation* attack{nullptr};
    [[maybe_unnused]]RAnimation* push{nullptr};
    [[maybe_unnused]]RAnimation* aim{nullptr};

private:
};