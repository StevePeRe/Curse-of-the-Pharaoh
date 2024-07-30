#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include <engines/graphic/SBone.hpp>
#include <engines/graphic/RAnimation.hpp>


class SAnimator	{
    public:
        // SAnimator(RAnimation* animation);
        void UpdateAnimation(float dt);
        void PlayAnimation(RAnimation* pAnimation);
        void PlayAnimationEnemies(RAnimation* pAnimation);
        void CalculateBoneTransform(const RAnimation::AssimpNodeData* node, glm::mat4 parentTransform);
        std::vector<glm::mat4> GetFinalBoneMatrices();
        void changeAnimation(RAnimation* animation);
        void setAnimation(RAnimation* animation);
        bool checkEndAnimation();
        bool hasAnimationEnded();
        void blendMyAnimations(float dt);
        void CalculateMyBlendedBoneTransform(const RAnimation::AssimpNodeData*, const RAnimation::AssimpNodeData*, float, float, const glm::mat4&, float);

        RAnimation* getCurrentAnimation() { return m_CurrentAnimation; }


    private:

        std::vector<glm::mat4> m_FinalBoneMatrices {};
        RAnimation* m_CurrentAnimation {};
        RAnimation* m_previousAnimation {};
        RAnimation* m_NextAnimation {};
        float m_CurrentTime {};
        float m_DeltaTime {};
        float m_factor {};
        bool looped {false};	
};