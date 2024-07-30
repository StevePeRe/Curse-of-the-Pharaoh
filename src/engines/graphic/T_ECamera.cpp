#include <engines/graphic/T_ECamera.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
// TODO Graphic quitar iostream pesa mucho
#include <iostream>

void T_ECamera::draw([[maybe_unused]]GraphicEngine *ge, [[maybe_unused]]TNode *node)
{
    //std::cout << "Entro draw camera" << std::endl;
}

// GETs
glm::mat4 T_ECamera::getCameraMatrix()
{
    // El primer parametro es el fovy
    return glm::perspective(glm::radians(fovy), (float)1920 / (float)1080, near, far);
}
glm::mat4 T_ECamera::GetViewMatrix()
{
    // target_ = glm::vec3(0, 0, -1);
    return glm::lookAt(position_, target_, up_);
}
glm::vec3 T_ECamera::getTarget()
{
    return target_;
}
glm::vec3 T_ECamera::getPosition()
{
    return position_;
}
glm::vec3 T_ECamera::getUp()
{
    return up_;
}
float T_ECamera::getFovy()
{
    return fovy;
}

// SETs
void T_ECamera::setPosition(glm::vec3 position)
{
    position_ = position;
}
void T_ECamera::setTarget(glm::vec3 front)
{
    target_ = front;
}
void T_ECamera::setFovy(float fovyAux)
{
    fovy = fovyAux;
}
void T_ECamera::setUp(glm::vec3 up)
{
    up_ = up;
}