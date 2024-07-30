#include <engines/graphic/SSkinMesh.hpp>
#include <engines/graphic/RShader.hpp>
#include <engines/graphic/RTexture.hpp>

SSkinMesh::SSkinMesh(std::vector<AVertex> vertices, std::vector<unsigned int> indices, RTexture* textures) { //
    this->vertices_ = vertices;
    this->indices_  = indices;
    this->textures_ = textures;
        
    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    setupMesh();
}



void SSkinMesh::addTexture(RTexture* textures) {
    textures_ = textures;
}

// SAnimator* SSkinMesh::getAnimator(){
//     return &animator;
// }


// initializes all the buffer objects/arrays
void SSkinMesh::setupMesh() {
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(AVertex), &vertices_[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AVertex), (void*)0);
    // Artex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AVertex), (void*)offsetof(AVertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AVertex), (void*)offsetof(AVertex, TexCoords));


    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(AVertex), (void*)offsetof(AVertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(AVertex), (void*)offsetof(AVertex, Bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(AVertex), (void*)offsetof(AVertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(AVertex), (void*)offsetof(AVertex, m_Weights));

    glBindVertexArray(0);
}

void SSkinMesh::draw(RShader &shader) {
    glActiveTexture(GL_TEXTURE0);
    if (textures_ != nullptr) {
        glUniform1i(glGetUniformLocation(shader.ID, "Texture"), 0);
        glBindTexture(GL_TEXTURE_2D, textures_->id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices_.size()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

// SBoundingBox SSkinMesh::getBoundingBox() {
//     SBoundingBox bb { vertices_.at(0).Position.x, vertices_.at(0).Position.x, 
//                       vertices_.at(0).Position.y, vertices_.at(0).Position.y, 
//                       vertices_.at(0).Position.z, vertices_.at(0).Position.z };

//     for (int i = 0; i < vertices_.size(); i++) {
//         if (vertices_.at(i).Position.x < bb.MinEdge.x) bb.MinEdge.x = vertices_.at(i).Position.x;
//         if (vertices_.at(i).Position.x > bb.MaxEdge.x) bb.MaxEdge.x = vertices_.at(i).Position.x;
//         if (vertices_.at(i).Position.y < bb.MinEdge.y) bb.MinEdge.y = vertices_.at(i).Position.y;
//         if (vertices_.at(i).Position.y > bb.MaxEdge.y) bb.MaxEdge.y = vertices_.at(i).Position.y;
//         if (vertices_.at(i).Position.z < bb.MinEdge.z) bb.MinEdge.z = vertices_.at(i).Position.z;
//         if (vertices_.at(i).Position.z > bb.MaxEdge.z) bb.MaxEdge.z = vertices_.at(i).Position.z;
//     }
//     return bb;
//}