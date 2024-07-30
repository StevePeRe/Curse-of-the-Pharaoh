#include <engines/graphic/SAnimator.hpp>
#include <engines/graphic/RSkinModel.hpp>

// SAnimator::SAnimator(RAnimation* animation)
// {
//     m_CurrentTime = 0.0;
//     m_CurrentAnimation = animation;

//     m_FinalBoneMatrices.reserve(100);

//     for (int i = 0; i < 100; i++)
//         m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
// }

void SAnimator::UpdateAnimation(float dt)
{
    m_DeltaTime = dt;
    // m_factor += 0.3;
    if (m_CurrentAnimation)
    {   
        m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * dt;
        if(checkEndAnimation()){
            m_CurrentTime -= m_CurrentAnimation->GetDuration();
            looped = true;
        }
        CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
    }
}

void SAnimator::PlayAnimation(RAnimation* pAnimation)
{
    //m_CurrentAnimation = m_NextAnimation;
    m_NextAnimation = pAnimation;
    looped = false;
    m_CurrentTime = 0.0f;
    m_factor = 0.0f;
}

void SAnimator::PlayAnimationEnemies(RAnimation* pAnimation)
{
    m_CurrentAnimation = pAnimation;
    m_CurrentTime = 0.0f;
}

void SAnimator::CalculateBoneTransform(const RAnimation::AssimpNodeData* node, glm::mat4 parentTransform)
{
    std::string nodeName = node->name;
    glm::mat4 nodeTransform = node->transformation;
    SBone* bone = m_CurrentAnimation->FindBone(nodeName);

    if (bone)
    {
        bone->Update(m_CurrentTime);
        nodeTransform = bone->GetLocalTransform();
    }

    glm::mat4 globalTransformation = parentTransform * nodeTransform;

    auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end())
    {
        int index = boneInfoMap[nodeName].id;
        glm::mat4 offset = boneInfoMap[nodeName].offset;
        m_FinalBoneMatrices.at(index);
        m_FinalBoneMatrices[index] = globalTransformation * offset;
        

    }
            

    for (int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);
}

std::vector<glm::mat4> SAnimator::GetFinalBoneMatrices() 
{ 
    return m_FinalBoneMatrices;  
}


void SAnimator::changeAnimation(RAnimation* animation)
{
    m_CurrentTime = 0.0;
    m_CurrentAnimation = animation;
    looped = false;
    m_FinalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
        m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
}


bool SAnimator::checkEndAnimation(){
    return m_CurrentTime >= m_CurrentAnimation->GetDuration();
}

bool SAnimator::hasAnimationEnded(){
    return looped;
}

void SAnimator::setAnimation(RAnimation* animation){
    m_CurrentTime = 0.0;
    m_CurrentAnimation = animation;
    m_NextAnimation = animation;
    looped = false;
    m_FinalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
        m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
}


void SAnimator::blendMyAnimations(float dt){
    // Animations has to have the same duration, so we have to stablish a relation between them.
    // Seen in https://stackoverflow.com/questions/69860756/how-do-i-correctly-blend-between-skeletal-animations-in-opengl-from-a-walk-anima
    // if (blendFactor => 1.0f){
    //     CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
    //     return;
    // }
    if(m_CurrentAnimation == m_NextAnimation) {UpdateAnimation(dt); return;};

    m_factor += 0.2f;
    if(m_factor >= 1.0f) {m_factor = 1.0f; m_CurrentAnimation = m_NextAnimation;}

    float a = 1.0;
    float b = (float)m_CurrentAnimation->GetDuration() / (float)m_NextAnimation->GetDuration();

    const float speedMultiplierCurrent = (1.0f - m_factor) * a + b * m_factor;


    a = (float)m_NextAnimation->GetDuration() / (float)m_CurrentAnimation->GetDuration();
    b = 1.0f;

    const float speedMultiplierNext = (1.0f - m_factor) * a + b * m_factor;

    static float currentTimeCurrent = 0.0f;
    currentTimeCurrent += (float)m_CurrentAnimation->GetTicksPerSecond() * dt * speedMultiplierCurrent;
    currentTimeCurrent = (float)fmod(currentTimeCurrent, m_CurrentAnimation->GetDuration());

    static float currentTimeNext = 0.0f;
    currentTimeNext += (float)m_NextAnimation->GetTicksPerSecond() * dt * speedMultiplierNext;
    currentTimeNext = (float)fmod(currentTimeNext, m_NextAnimation->GetDuration());

    //Then, we have to calculate the transform

    CalculateMyBlendedBoneTransform(&m_CurrentAnimation->GetRootNode(), &m_NextAnimation->GetRootNode(), currentTimeCurrent, currentTimeNext, glm::mat4(1.0f), m_factor);
}

void SAnimator::CalculateMyBlendedBoneTransform(const RAnimation::AssimpNodeData* currentNode, const RAnimation::AssimpNodeData* nextNode, float currentTimeCurrent, float currentTimeNext, const glm::mat4& parentTransform, float blendFactor){
    
    
    const std::string nodeName = currentNode->name;

    //Get the two transform matrices
    glm::mat4 currentNodeTransform = currentNode->transformation;
    SBone* CurrentBone = m_CurrentAnimation->FindBone(nodeName);

    if (CurrentBone)
    {
        CurrentBone->Update(currentTimeCurrent);
        currentNodeTransform = CurrentBone->GetLocalTransform();
    }

    glm::mat4 nextNodeTransform = nextNode->transformation;
    SBone* nextBone = m_NextAnimation->FindBone(nodeName);

    if (nextBone)
    {
        nextBone->Update(currentTimeNext);
        nextNodeTransform = nextBone->GetLocalTransform();
    }

    //Time to blend between these matrices
    const glm::quat CurrentRot = glm::quat_cast(currentNodeTransform);
    const glm::quat nextRot = glm::quat_cast(nextNodeTransform);

    const glm::quat finalRot = glm::slerp(CurrentRot, nextRot, blendFactor);
    glm::mat4 blendedMatrix = glm::mat4_cast(finalRot);
    glm::vec3 blendTranslate = (1.0f - blendFactor) * currentNodeTransform[3] + nextNodeTransform[3] * blendFactor;
    glm::mat4 translatedMatrix = glm::translate(glm::mat4(1.0f), blendTranslate);
    glm::mat4 globalTransformation = parentTransform * translatedMatrix * blendedMatrix;

    auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end())
    {
        int index = boneInfoMap[nodeName].id;
        glm::mat4 offset = boneInfoMap[nodeName].offset;
        m_FinalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < currentNode->childrenCount; i++)
        CalculateMyBlendedBoneTransform(&currentNode->children[i], &nextNode->children[i], currentTimeCurrent, currentTimeNext, globalTransformation, blendFactor);
}





// void SAnimator::blendAnimations(RAnimation* prevAnimation, RAnimation* nextAnimation, float blendFactor, float dt){
//     // Animations has to have the same duration, so we have to stablish a relation between them.
//     // Seen in https://stackoverflow.com/questions/69860756/how-do-i-correctly-blend-between-skeletal-animations-in-opengl-from-a-walk-anima
//     if (blendFactor >= 1.0f){
        
//         return;
//     }
    
//     float a = 1.0;
//     float b = prevAnimation->getDuration() / nextAnimation->getDuration();

//     const float speedMultiplierPrev = (1.0f - blendFactor) * a + b * blendFactor;


//     float a = nextAnimation->getDuration() / prevAnimation->getDuration();
//     float b = 1.0;

//     const float speedMultiplierNext = (1.0f - blendFactor) * a + b * blendFactor;

//     static float currentTimePrev = 0.0f;
//     currentTimePrev += prevAnimation->GetTicksPerSecond() * dt * speedMultiplierPrev;
//     currentTimePrev = fmod(currentTimePrev, prevAnimation->GetDuration());

//     static float currentTimeNext = 0.0f;
//     currentTimeNext += nextAnimation->GetTicksPerSecond() * dt * speedMultiplierNext;
//     currentTimeNext = fmod(currentTimeNext, nextAnimation->GetDuration());

//     //Then, we have to calculate the transform

//     CalculateBlendedBoneTransform(prevAnimation, &prevAnimation->GetRootNode(), nextAnimation, &nextAnimation->GetRootNode(), currentTimePrev, currentTimeNext, glm::mat4(1.0f), blendFactor);
// }

// void SAnimator::blendNextAnimation(RAnimation* nextAnimation, float blendFactor, float dt){
//     // Animations has to have the same duration, so we have to stablish a relation between them.
//     // Seen in https://stackoverflow.com/questions/69860756/how-do-i-correctly-blend-between-skeletal-animations-in-opengl-from-a-walk-anima
    
//     float a = 1.0;
//     float b = m_CurrentAnimation->getDuration() / nextAnimation->getDuration();

//     const float speedMultiplierPrev = (1.0f - blendFactor) * a + b * blendFactor;


//     float a = nextAnimation->getDuration() / m_CurrentAnimation->getDuration();
//     float b = 1.0;

//     const float speedMultiplierNext = (1.0f - blendFactor) * a + b * blendFactor;

//     static float currentTimePrev = 0.0f;
//     currentTimePrev += m_CurrentAnimation->GetTicksPerSecond() * dt * speedMultiplierPrev;
//     currentTimePrev = fmod(currentTimePrev, m_CurrentAnimation->GetDuration());

//     static float currentTimeNext = 0.0f;
//     currentTimeNext += nextAnimation->GetTicksPerSecond() * dt * speedMultiplierNext;
//     currentTimeNext = fmod(currentTimeNext, nextAnimation->GetDuration());

//     //Then, we have to calculate the transform

//     CalculateBlendedBoneTransform(m_CurrentAnimation, &m_CurrentAnimation->GetRootNode(), nextAnimation, &nextAnimation->GetRootNode(), currentTimePrev, currentTimeNext, glm::mat4(1.0f), blendFactor);
// }

// void SAnimator::CalculateBlendedBoneTransform(RAnimation* prevAnimation, const AssimpNodeData* prevNode, RAnimation* nextAnimation, const AssimpNodeData* nextNode, float currentTimePrev, float currentTimeNext, glm::mat4(1.0f), float blendFactor){
    

//     // if (blendFactor => 1.0f){
//     //     m_CurrentAnimation = nextAnimation;
//     //     UpdateAnimation(dt)
//     //     //CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
//     //     return;
//     // }

//     const std::string nodeName = prevNode->name;

//     //Get the two transform matrices
//     glm::mat4 prevNodeTransform = prevNode->transformation;
//     SBone* prevBone = prevAnimation->FindBone(prevNodeName);

//     if (prevBone)
//     {
//         prevBone->Update(currentTimePrev);
//         prevNodeTransform = prevBone->GetLocalTransform();
//     }

//     glm::mat4 nextNodeTransform = nextNode->transformation;
//     SBone* nextBone = nextAnimation->FindBone(nextNodeName);

//     if (nextBone)
//     {
//         nextBone->Update(currentTimenext);
//         nextNodeTransform = nextBone->GetLocalTransform();
//     }

//     //Time to blend between these matrices
//     const glm::quat prevRot = glm::quat_cast(prevNodeTransform);
//     const glm::quat nextRot = glm::quat_cast(nextNodeTransform);

//     const glm::quat finalRot = glm::slerp(prevRot, nextRot, blendFactor);
//     glm::mat4 blendedMatrix = glm::mat4_cast(finalRot);

//     blendedMatrix[3] = (1.0f - blendFactor) * prevNodeTransform[3] + nextNodeTransform[3] * blendFactor;



//     glm::mat4 globalTransformation = parentTransform * blendedMatrix;

//     auto boneInfoMap = prevAnimation->GetBoneIDMap();
//     if (boneInfoMap.find(nodeName) != boneInfoMap.end())
//     {
//         int index = boneInfoMap[nodeName].id;
//         glm::mat4 offset = boneInfoMap[nodeName].offset;
//         m_FinalBoneMatrices[index] = globalTransformation * offset;
//     }

//     for (int i = 0; i < node->childrenCount; i++)
//         CalculateBlendedBoneTransform(prevAnimation, &prevNode->children[i], nextAnimation, &nextNode->children[i], currentTimePrev, currentTimeNext, globalTransformation, blendFactor);
// }