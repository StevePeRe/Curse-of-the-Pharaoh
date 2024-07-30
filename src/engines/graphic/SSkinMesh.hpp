#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GLAD/src/glad.h>
#include <string>

#include <engines/graphic/RTexture.hpp>
// #include <engines/graphic/SBoundingBox.hpp>

struct RShader;
struct RTexture;

#define MAX_BONE_INFLUENCE 4

struct AVertex
{
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;

    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;

    // bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    // weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct SSkinMesh
{
    SSkinMesh(std::vector<AVertex> vertices, std::vector<unsigned int> indices, RTexture* textures); //
    void draw(RShader &shader);
    void addTexture(RTexture *);
    void setupMesh();
    // SBoundingBox getBoundingBox();
    std::vector<AVertex> vertices_;
    std::vector<unsigned int> indices_;
    RTexture* textures_;
    unsigned int VAO, VBO, EBO;
};