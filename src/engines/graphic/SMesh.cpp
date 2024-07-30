#include <engines/graphic/SMesh.hpp>
#include <GLAD/src/glad.h>
#include <iostream>

SMesh::SMesh(std::vector<MeshBuild> build, std::vector<unsigned int> index)
{
    this->build = build;
    this->index = index;
    // Se hace aqui para que en la pantalla de carga se creen los buffers
    setupMesh();
}
void SMesh::draw(RShader &shader)
{
    glActiveTexture(GL_TEXTURE0);
    if (texture != nullptr) {
        glUniform1i(glGetUniformLocation(shader.ID, "Texture"), 0);
        glBindTexture(GL_TEXTURE_2D, texture->id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(index.size()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
void SMesh::setupMesh() {
    // create buffers/arrays

    // Estas variables las utilizamos como posiciones de memoria para guardar la informacion
    // de la malla en este caso generamos buffers donde va a ir la malla
    // VAO -> Vertex array object
    // VBO -> Vertex buff object
    // EBO -> Texture coords
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Para mallas 3d
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, build.size() * sizeof(MeshBuild), &build[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), &index[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshBuild), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshBuild), (void*)offsetof(MeshBuild, normals));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshBuild), (void*)offsetof(MeshBuild, texCoords));

    glBindVertexArray(0);
}
void SMesh::setTexture(RTexture *texture, RMaterial *material)
{
    this->material = material;
    this->texture = texture;
}