#include <engines/graphic/T_ESkyBox.hpp>
#include <engines/graphic/GraphicEngine.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>

T_ESkyBox::T_ESkyBox(std::array<std::string, 6> faces)
{
    float skyboxVertices[] = {
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f};

    unsigned int skyboxIndices[] = {
        1, 2, 6,
        6, 5, 1,

        0, 4, 7,
        7, 3, 0,

        4, 5, 6,
        6, 7, 4,

        0, 3, 2,
        2, 1, 0,

        0, 1, 5,
        5, 4, 0,

        3, 7, 6,
        6, 2, 3};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    RTexture tex;
    textureId = tex.TextureToCubemap(faces);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void T_ESkyBox::draw(GraphicEngine *ge, [[maybe_unused]]TNode *node)
{
    glDisable(GL_CULL_FACE);

    glDepthFunc(GL_LEQUAL);

    auto *camera = ge->getActiveCamera();
    auto *c = camera->getEntity<T_ECamera>();
    RShader *shader = ge->resManager->add<RShader>("skybox");

    shader->use();
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::mat3(c->GetViewMatrix());

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)1920 / 1080, 0.1f, 100.0f);

    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);

    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}