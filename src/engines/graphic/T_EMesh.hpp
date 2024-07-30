#pragma once

#include <engines/graphic/TEntity.hpp>
#include <engines/graphic/RModel.hpp>
#include <engines/graphic/TNode.hpp>
#include <GLAD/src/glad.h>
#include <string>

struct TNode;

// La malla hereda de Entity
struct T_EMesh : public TEntity
{
    T_EMesh() = default;
    explicit T_EMesh(RModel *model, glm::vec3 LightColor, glm::vec3 LightDirection, float diffuse, float ambient, float specular) : 
        mesh{model}, LightColor_{LightColor}, LightDirection_{LightDirection}, diffuse_{diffuse}, ambient_{ambient}, specular_{specular} {}
    void draw(GraphicEngine *ge, TNode *node);
    void loadMesh(std::string path);

    RModel* mesh;

    private:
        // Parametros de la malla
        //RModel* mesh;
        //glm::vec3 color_{0.5f,0.5f,0.5f};
        glm::vec3 LightColor_{1.0f,0.948f,0.0f};
        glm::vec3 LightDirection_{1.0f,0.948f,0.0f};
        float diffuse_{0.7f};
        float ambient_{0.7f};
        float specular_{0.7f};
};