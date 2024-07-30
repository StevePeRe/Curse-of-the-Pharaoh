#include <engines/graphic/TNode.hpp>
#include <engines/graphic/TNodeTree.hpp>
#include <algorithm>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

TNode::TNode(TNodeTree &tree, key_type par, key_type idMe, const glm::vec3 pos, const glm::vec3 rot, const glm::vec3 sca)
    : nodeTree(tree), id(idMe), position(pos), rotation(rot), scale(sca)
{
    if (par)
    {
        parent = par;
        nodeTree.getById(parent)->addChild(idMe);
    }
}

TNode::~TNode()
{
    // for (size_t i = 0; i < childrenList.size(); i++)
    // {
    //     nodeTree.getById(childrenList[i])->~TNode();
    // }
    // auto &parentChildren = nodeTree.getById(parent)->childrenList;
    // auto it = std::find(parentChildren.begin(), parentChildren.end(), this->id);
    // parentChildren.erase(it);
    // nodeTree.deleteNode(this->id);

    auto children_ids_ = childrenList; 
    for(auto child_id : children_ids_){
        nodeTree.getById(child_id)->~TNode();
    }

    auto* parent_   = nodeTree.getById(parent);
    auto& brothers = parent_->childrenList; 
    auto it = std::find(brothers.begin(), brothers.end(), id);
    brothers.erase(it);
    nodeTree.deleteNode(id);
}

void TNode::treeIterator(GraphicEngine *ge)
{
    // std::cout << "Entro en el tree" << std::endl;
    //  Si padre es invisible no lo dibujamos y tampoco a los hijos
    if (!visible)
        return;

    // Si ponemos la condicion de visible aqui solo no dibujamos el padre pero los hijos si
    if (entity != nullptr)
    {
        // std::cout << "Entro en el entity" << std::endl;
        entity->draw(ge, this);
    }

    // std::cout << "Paso del entity" << std::endl;

    for (size_t i = 0; i < childrenList.size(); i++)
    {
        // std::cout << "ENTRO en el FOR" << std::endl;
        nodeTree.getById(childrenList[i])->treeIterator(ge);
    }

    // std::cout << "Salgo del tree" << std::endl;
    //  Ya has dibujado entonnces por ahora no necesitas volver a calcular la matrix hasta que se mueva el objeto
    setUpdateMatrix(false);
}

const glm::mat4 TNode::getRelativeMatrix()
{
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
    if(std::isnan(glm::length(rotation))) {
        rotation = lastRotation;
    } else{
        lastRotation = rotation;
    }
    matrix = glm::rotate(matrix, lastRotation.x, {1.f, 0.f, 0.f});
    matrix = glm::rotate(matrix, lastRotation.y, {0.f, 1.f, 0.f});
    if (scale != glm::vec3(1.f, 1.f, 1.f))
        matrix = glm::scale(matrix, scale);

    return matrix;
}

void TNode::addChild(key_type childToAdd)
{
    if (childToAdd != 0 && childToAdd != this->id)
    {
        childrenList.push_back(childToAdd);
        nodeTree.getById(childToAdd)->parent = this->id;
    }
}

void TNode::removeChild(key_type childToRemove)
{
    if (childToRemove && childToRemove != this->id)
    {
        // Iteramos desde el principio del vector hasta el final para encontrar el childToRemove
        auto childToFindIt = std::find(childrenList.begin(), childrenList.end(), childToRemove);
        childrenList.erase(childToFindIt);
        nodeTree.getById(childToRemove)->parent = 0;
    }
}

void TNode::clearChild()
{
    auto childrenIds = childrenList;
    for (auto child : childrenIds)
    {
        nodeTree.getById(child)->~TNode();
    }
}

void TNode::translate(const glm::vec3 posToTranslate)
{
    updateMatrix = true;
    position += posToTranslate;
}
void TNode::rotate(const glm::vec3 rotToTranslate)
{
    updateMatrix = true;
    rotation += rotToTranslate;
}

glm::vec3 TNode::getModelDirection() {
    viewMatrixPlayer = this->getRelativeMatrix();
    
    entityForward = glm::vec3(viewMatrixPlayer[2]);
    if(entityForward.length() > 0)
        entityForward = glm::normalize(entityForward);
    entityForward.y = 0.f;
    return entityForward;
}

void TNode::rotateInterpolate(const glm::vec3 rotToTranslate)
{
    updateMatrix = true;
    /* entityForward =  */getModelDirection();

    if ((glm::length(entityForward) * glm::length(rotToTranslate)) != 0)
    { // no debe dividir entre 0
        auto angle = glm::acos(dot(entityForward, rotToTranslate) / (glm::length(entityForward) * glm::length(rotToTranslate)));
        glm::vec3 crossProduct = glm::cross(entityForward, rotToTranslate);
        float determinant = crossProduct.y;
        if (determinant < 0)
        {
            angle = -angle; // Si el determinante es negativo, invierte el ángulo
        }
        if (glm::abs(angle) <= 0.04f)
            angle = 0.f; // para que no haya desbordamiento

        auto angleDegrees = glm::degrees(angle);
        rotationVector = angleDegrees * 0.005f * glm::vec3{0.f, 1.f, 0.f};
    }

    rotation += rotationVector;
}
void TNode::scaleVec(const glm::vec3 scaToTranslate)
{
    updateMatrix = true;
    scale += scaToTranslate;
}
void TNode::setUpdateMatrix(bool updateMatrix)
{
    this->updateMatrix = updateMatrix;
    for (size_t i = 0; i < childrenList.size(); i++)
    {
        nodeTree.getById(childrenList[i])->setUpdateMatrix(updateMatrix);
    }
}
// void TNode::updateAbsolutePosition()
// {
//     if (parent == 0)
//     {
//         auto *parentAux = nodeTree.getById(parent);

//     }
// }
void TNode::setPosition(const glm::vec3 pos)
{
    updateMatrix = true;
    position = pos;
}
void TNode::setRotation(const glm::vec3 rot)
{
    updateMatrix = true;
    rotation = rot;
}
void TNode::setScale(const glm::vec3 sca)
{
    updateMatrix = true;
    scale = sca;
}
const glm::vec3 TNode::getPosition() const
{
    return position;
}
const glm::vec3 TNode::getRotation() const
{
    return rotation;
}
const glm::vec3 TNode::getScale() const
{
    return scale;
}
void TNode::setEntity(std::unique_ptr<TEntity> entityToSet)
{
    entity = std::move(entityToSet);
}