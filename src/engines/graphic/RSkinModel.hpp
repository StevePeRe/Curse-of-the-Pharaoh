#pragma once 

#include <engines/graphic/RModel.hpp>
#include <engines/graphic/SSkinMesh.hpp>
#include <engines/graphic/RMaterial.hpp>
#include <map>

#include <memory>

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;

    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;

};

struct RSkinModel : RModel {
    RSkinModel();
    void loadResource(std::string filename);
    void loadModel(std::string const &filename);
    void draw(RShader &shader);
    void processNode(aiNode *node, const aiScene *scene);
    std::unique_ptr<SSkinMesh> processMesh(aiMesh *mesh, const aiScene *scene);
    
    void addTexture(RTexture*, RMaterial*);
    std::vector<RTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);


    void SetVertexBoneDataToDefault(AVertex& vertex);
    void SetVertexBoneData(AVertex& vertex, int boneID, float weight);
    void ExtractBoneWeightForVertices(std::vector<AVertex>& vertices, aiMesh* mesh, const aiScene* scene);


    auto& GetBoneInfoMap() { return m_BoneInfoMap; }
    int& GetBoneCount() { return m_BoneCounter; } 
    //SBoundingBox getBoundingBox();

    private:
        RTexture* skin_textures_loaded{};
        std::vector<std::unique_ptr<SSkinMesh>> skinMeshes_ {};
        std::map<std::string, BoneInfo> m_BoneInfoMap{}; 
        // SAnimator animator;
        int m_BoneCounter = 0;
};