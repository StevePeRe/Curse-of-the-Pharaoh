#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <engines/graphic/RTexture.hpp>
#include <engines/graphic/RShader.hpp>
#include <engines/graphic/RMaterial.hpp>

struct MeshBuild 
{
    glm::vec3 vertex;
    glm::vec3 normals;
    glm::vec2 texCoords;
};

struct SMesh
{
    explicit SMesh(std::vector<MeshBuild> build, std::vector<unsigned int> index);
    void draw(RShader &shader);
    void setupMesh();
    void setTexture(RTexture *texture, RMaterial *material);

    private:
        std::vector<MeshBuild> build;
        std::vector<unsigned int> index; 
        RTexture* texture;
        RMaterial* material;
        // Shaders y optimizacion
        unsigned int VAO, VBO, EBO;
};