#include <engines/graphic/T_EBillboard.hpp>
#include <engines/graphic/GraphicEngine.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

T_EBillboard::T_EBillboard(unsigned int id)
{
    setVertex();
    textureId = id;
}

void T_EBillboard::setVertex()
{

    float bbVertices[] = {
        // positions          // colors           // texture coords
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f  // bottom right
    };
    // float bbVertices[] = {
    //     0.0f, -1.0f, 1.0f,
    //     0.0f, -1.0f, -1.0f,
    //     0.0f, 1.0f, -1.0f,
    //     0.0f, -1.0f, 1.0f,
    //     0.0f, 1.0f, -1.0f,
    //     0.0f, 1.0f, 1.0f};

    unsigned int bbIndices[] = {
        0, 1, 2,
        0, 3, 2};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bbVertices), bbVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bbIndices), bbIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void T_EBillboard::draw(GraphicEngine *ge, TNode *node)
{
    glDisable(GL_CULL_FACE);

    auto *camera = ge->getActiveCamera();
    auto *c = camera->getEntity<T_ECamera>();
    RShader *shader = ge->resManager->add<RShader>("billboard");

    shader->use();
    glm::mat4 view = c->GetViewMatrix();
    glm::mat4 projection = c->getCameraMatrix();
    glm::mat4 model = node->getRelativeMatrix();

    glm::vec3 cameraPos = c->getPosition();
    glm::vec3 objectPos = node->getPosition();

    glm::vec3 objectToCamera = glm::normalize(cameraPos - objectPos);

    glm::vec3 objectUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 objectRight = glm::normalize(glm::cross(objectUp, objectToCamera));

    glm::vec3 objectNewUp = glm::normalize(glm::cross(objectToCamera, objectRight));

    float [[maybe_unused]] tx = glm::dot(cameraPos, objectRight);
    float [[maybe_unused]] ty = glm::dot(cameraPos, objectNewUp);
    float [[maybe_unused]] tz = glm::dot(cameraPos, objectToCamera);

    glm::mat4 rotation = glm::mat4(glm::vec4(objectRight, 0.0f),
                                   glm::vec4(objectNewUp, 0.0f),
                                   glm::vec4(-objectToCamera, 0.0f),
                                   glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    model *= rotation;

    if (node->getEntity<SParticle>() != nullptr)
    {
        shader->setVec3("particleColor", node->getEntity<SParticle>()->color);
    }
    else
    {
        // Revisar esto colores particulas
        shader->setVec3("particleColor", {1.0f,1.0f,1.0f});
    }

    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setMat4("model", model);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}