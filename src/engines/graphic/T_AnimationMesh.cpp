#include <engines/graphic/T_AnimationMesh.hpp>
#include <engines/graphic/GraphicEngine.hpp>
#include <iostream>

T_AnimationMesh::T_AnimationMesh(RSkinModel *model)
{
    model_ = model;
}

void T_AnimationMesh::loadMesh(std::string)
{
}

void T_AnimationMesh::draw(GraphicEngine *ge, TNode *node)
{

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_CLAMP);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    auto *c = ge->getActiveCamera()->getEntity<T_ECamera>();

    RShader *ourShader{};
    ourShader = ge->resManager->add<RShader>("animation");
    ourShader->use();

    // Get data from bones and send this to shader
    auto transforms = animator_.GetFinalBoneMatrices();
    for (int i = 0; i < (int)transforms.size(); ++i)
        ourShader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

    // Get PVM Matrix from camera matrix and model relative transformation
    glm::mat4 projection = c->getCameraMatrix();
    glm::mat4 view = c->GetViewMatrix();
    glm::mat4 models = node->getRelativeMatrix();

    // Send PVM Matrix to shader
    ourShader->setMat4("projection", projection);
    ourShader->setMat4("view", view);
    ourShader->setMat4("model", models);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    model_->draw(*ourShader);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

// void T_AnimationMesh::setBorder(glm::vec4 color, double width)
// {
//     borderColor_ = color;
//     borderWidth_ = width;
// }

// void T_AnimationMesh::isSpawning()
// {
//     texture_value_ = 0.0;
//     noise_value_ = 0.5;
// }
