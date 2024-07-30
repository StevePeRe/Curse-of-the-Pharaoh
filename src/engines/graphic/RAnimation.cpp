#include <engines/graphic/RAnimation.hpp>
#include <engines/graphic/RModel.hpp>
#include <engines/graphic/SBone.hpp>
#include <engines/graphic/assimp_glm_helpers.hpp>

RAnimation::RAnimation(){
}


void RAnimation::loadResource(std::string filename){
    this->setName(filename);
}

void RAnimation::loadAnimation(std::string const &animationPath, RSkinModel* model){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
     if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        return;
    }
    // assert(scene && scene->mRootNode);
    auto animation = scene->mAnimations[0];
    m_Duration = animation->mDuration;
    m_TicksPerSecond = animation->mTicksPerSecond;
    ReadHeirarchyData(m_RootNode, scene->mRootNode);
    ReadMissingBones(animation, *model);
}

SBone* RAnimation::FindBone(const std::string& name)
{
    auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
        [&](const SBone& bone)
        {
            return bone.GetBoneName() == name;
        }
    );
    if (iter == m_Bones.end()) return nullptr;
    else return &(*iter);
}


void RAnimation::ReadMissingBones(const aiAnimation* animation, RSkinModel& model)
{
    int size = animation->mNumChannels;
    auto& boneInfoMap = model.GetBoneInfoMap();//getting m_BoneInfoMap from Model class
    int& boneCount = model.GetBoneCount(); //getting the m_BoneCounter from Model class
    m_Bones.clear();
    //reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++)
    {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;
        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            boneInfoMap[boneName].id = boneCount;
            boneCount++;
        }
        else{
            m_Bones.push_back(SBone(channel->mNodeName.data,
                boneInfoMap[channel->mNodeName.data].id, channel));
        }
        
    }
    m_BoneInfoMap = boneInfoMap;
}

void RAnimation::ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src)
{
    assert(src);
    dest.children.clear();
    dest.name = src->mName.data;
    dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;
    for (uint32_t i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData newData;
        ReadHeirarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}