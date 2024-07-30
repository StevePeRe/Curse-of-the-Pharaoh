#include <engines/graphic/T_EMesh.hpp>
#include <engines/graphic/GraphicEngine.hpp>
#include <iostream>

void T_EMesh::draw(GraphicEngine *ge, TNode *node)
{

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_CLAMP);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //std::cout << "Hasta aqui llego" << std::endl;
    // Cogemos la active camera
    auto *camera = ge->getActiveCamera()->getEntity<T_ECamera>();

    //std::cout << "Camera target: " << camera->getTarget().x << std::endl;

    auto *shader = ge->resManager.get()->add<RShader>("model");

    shader->use();
    shader->setMat4("model", node->getRelativeMatrix());
    shader->setMat4("projection", camera->getCameraMatrix());
    shader->setMat4("view", camera->GetViewMatrix());
    
    //shader->setVec3("color", color_);
    shader->setVec3("LightColor", LightColor_);
    //shader->setVec3("LightDirection", LightDirection_);
    shader->setFloat("AmbientStrength", ambient_);
    //shader->setVec3("SpecularStrength", specular_);
    // if (ge->getLigths())
    //std::cout << "Antes de ir a pintar el mesh" << std::endl;
    mesh->draw(*shader);

    //std::cout << "Paso del draw" << std::endl;

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //std::cout << "Sali del draw de mesh" << std::endl;
}

void T_EMesh::loadMesh([[maybe_unused]]std::string path)
{

}