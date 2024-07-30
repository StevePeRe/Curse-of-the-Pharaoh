#pragma once

#include <engines/graphic/Resource.hpp>
#include <engines/graphic/SMesh.hpp>
#include <engines/graphic/RShader.hpp>
#include <string>
#include <vector>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <engines/graphic/RMaterial.hpp>

struct RModel : public Resource
{
    void loadResource(std::string fileName);
    void loadModel(std::string const fileName);
    void processNode(aiNode *node, const aiScene *scene);
    std::unique_ptr<SMesh> processMesh(aiMesh *mesh, const aiScene *scene);
    void addTexture(RTexture *texture, RMaterial *material);
    void draw(RShader &shader);

private:
    std::vector<std::unique_ptr<SMesh>> meshes;
};
