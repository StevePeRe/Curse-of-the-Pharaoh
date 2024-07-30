#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <engines/graphic/Resource.hpp>
#include <engines/graphic/RSkinModel.hpp>

struct SBone;

struct RAnimation : Resource
{

    struct AssimpNodeData
    {
        glm::mat4 transformation;
        std::string name;
        int childrenCount;
        std::vector<AssimpNodeData> children;
    };

    void loadResource(std::string filename);
    RAnimation();
    // ~RAnimation() = default;

    void loadAnimation(std::string const &filename, RSkinModel *model_);
    SBone *FindBone(const std::string &name);
    inline double GetTicksPerSecond() { return m_TicksPerSecond; };
    inline double GetDuration() { return m_Duration; };
    inline const AssimpNodeData &GetRootNode() { return m_RootNode; };
    inline const std::map<std::string, BoneInfo> &GetBoneIDMap() { return m_BoneInfoMap; };

    void setDuration(double duration) { m_Duration = duration; }

private:
    void ReadMissingBones(const aiAnimation *animation, RSkinModel &model);
    void ReadHeirarchyData(AssimpNodeData &dest, const aiNode *src);

    double m_Duration;
    double m_TicksPerSecond;
    std::vector<SBone> m_Bones;
    AssimpNodeData m_RootNode;
    std::map<std::string, BoneInfo> m_BoneInfoMap;
};
