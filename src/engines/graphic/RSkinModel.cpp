#include <engines/graphic/RSkinModel.hpp>
#include <engines/graphic/assimp_glm_helpers.hpp>



RSkinModel::RSkinModel(){}

void RSkinModel::loadResource(std::string filename){
    this->setName(filename);
    loadModel(filename);
}

void RSkinModel::draw(RShader &shader) {
    for(unsigned int i = 0; i < skinMeshes_.size(); i++)
        skinMeshes_[i]->draw(shader);
}


void RSkinModel::addTexture(RTexture* tex, RMaterial*) {
    for(unsigned int i = 0; i < skinMeshes_.size(); i++)
        skinMeshes_[i]->addTexture(tex);
}


// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
void RSkinModel::loadModel(std::string const &path) {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        return;
    }

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}


// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void RSkinModel::processNode(aiNode *node, const aiScene *scene) {
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        skinMeshes_.push_back(std::move(processMesh(mesh, scene)));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}


std::unique_ptr<SSkinMesh> RSkinModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<AVertex> vertices;
    std::vector<unsigned int> indices;
    RTexture* textures;

     for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        AVertex vertex;
        SetVertexBoneDataToDefault(vertex);

        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // // 1. diffuse maps
    // std::vector<RTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    // textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // // 2. specular maps
    // std::vector<RTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    // textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // // 3. normal maps
    // std::vector<RTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    // textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // // 4. height maps
    // std::vector<RTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    // textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    ExtractBoneWeightForVertices(vertices,mesh,scene);

    // vector dee texturas
    auto ssm = std::make_unique<SSkinMesh>(vertices, indices, textures); //, textures
    return std::move(ssm);
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<RTexture> RSkinModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    // std::vector<RTexture> textures;
    // for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    // {
    //     aiString str;
    //     mat->GetTexture(type, i, &str);
    //     // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
    //     bool skip = false;
    //     for(unsigned int j = 0; j < skin_textures_loaded.size(); j++)
    //     {
    //         if(std::strcmp(skin_textures_loaded[j].path.data(), str.C_Str()) == 0)
    //         {
    //             textures.push_back(skin_textures_loaded[j]);
    //             skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
    //             break;
    //         }
    //     }
    //     if(!skip)
    //     {   // if texture hasn't been loaded already, load it
    //         RTexture texture;

    //         texture.id = TextureFromFile(str.C_Str(), this->directory);
    //         texture.type = typeName;
    //         texture.path = str.C_Str();
    //         textures.push_back(texture);
    //         skin_textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
    //     }
    // }

    // return textures;
}


void RSkinModel::SetVertexBoneDataToDefault(AVertex& vertex)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        vertex.m_BoneIDs[i] = -1;
        vertex.m_Weights[i] = 0.0f;
    }
}


void RSkinModel::SetVertexBoneData(AVertex& vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
    {
        if (vertex.m_BoneIDs[i] < 0)
        {
            vertex.m_Weights[i] = weight;
            vertex.m_BoneIDs[i] = boneID;
            break;
        }
    }
}

void RSkinModel::ExtractBoneWeightForVertices(std::vector<AVertex>& vertices, aiMesh* mesh, [[maybe_unused]]const aiScene* scene){
    // auto& boneInfoMap = m_BoneInfoMap;
	// int& boneCount = m_BoneCounter;
    for (int boneIndex = 0; boneIndex < (int)mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (m_BoneInfoMap.find(boneName) == m_BoneInfoMap.end())
        {
            BoneInfo newBoneInfo;
            newBoneInfo.id = m_BoneCounter;
            newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(
                mesh->mBones[boneIndex]->mOffsetMatrix);
            m_BoneInfoMap[boneName] = newBoneInfo;
            boneID = m_BoneCounter;
            m_BoneCounter++;
        }
        else
        {
            boneID = m_BoneInfoMap[boneName].id;
        }
        assert(boneID != -1);
        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;
        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
            int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= (int)vertices.size());
            SetVertexBoneData(vertices[vertexId], boneID, weight);
        }
    }
}


// SBoundingBox RSkinModel::getBoundingBox() {
//     assert(skinMeshes_.size() >0);
//     SBoundingBox bb1 = skinMeshes_.at(0)->getBoundingBox();
//     SBoundingBox bb2;
//     for(unsigned int i = 1; i < skinMeshes_.size(); i++) {
//         bb2 = skinMeshes_.at(i)->getBoundingBox();
//         if(bb1.MinEdge.x > bb2.MinEdge.x) bb1.MinEdge.x = bb2.MinEdge.x;
//         if(bb1.MaxEdge.x < bb2.MaxEdge.x) bb1.MaxEdge.x = bb2.MaxEdge.x;
//         if(bb1.MinEdge.y > bb2.MinEdge.y) bb1.MinEdge.y = bb2.MinEdge.y;
//         if(bb1.MaxEdge.y < bb2.MaxEdge.y) bb1.MaxEdge.y = bb2.MaxEdge.y;
//         if(bb1.MinEdge.z > bb2.MinEdge.z) bb1.MinEdge.z = bb2.MinEdge.z;
//         if(bb1.MaxEdge.z < bb2.MaxEdge.z) bb1.MaxEdge.z = bb2.MaxEdge.z;
//     }
//     return bb1;
// }
