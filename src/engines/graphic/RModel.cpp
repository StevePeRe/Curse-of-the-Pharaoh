#include <engines/graphic/RModel.hpp>
#include <iostream>

void RModel::loadResource(std::string fileName)
{
    this->setName(fileName);
    loadModel(fileName);
}
void RModel::loadModel(std::string const fileName)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        return;
    }
    // retrieve the directory path of the filepath
    std::string directory = fileName.substr(0, fileName.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}
// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void RModel::processNode(aiNode *node, const aiScene *scene)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(std::move(processMesh(mesh, scene)));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
std::unique_ptr<SMesh> RModel::processMesh(aiMesh *mesh, [[maybe_unused]]const aiScene *scene)
{
    // data to fill
    std::vector<MeshBuild> vertices;
    std::vector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        MeshBuild meshBuild;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        meshBuild.vertex = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            meshBuild.normals = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            meshBuild.texCoords = vec;
        }
        else
            meshBuild.texCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(meshBuild);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // return a mesh object created from the extracted mesh data
    auto m = std::make_unique<SMesh>(vertices, indices);

    // Mira el return de un move que no hace falta hacerlo
    return std::move(m);
}
void RModel::draw(RShader &shader)
{
    //std::cout << "Aqui entro en el draw de RModel" << std::endl;
    for (size_t i = 0; i < meshes.size(); i++)
    {
        meshes[i]->draw(shader);        
    }
    //std::cout << "Salgo del draw de RModel" << std::endl;
}
void RModel::addTexture(RTexture *texture, RMaterial *material)
{
    for (size_t i = 0; i < meshes.size(); i++)
    {
        meshes[i]->setTexture(texture, material);
    }
}