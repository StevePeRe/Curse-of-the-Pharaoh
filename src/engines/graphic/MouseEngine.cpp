#include <engines/graphic/MouseEngine.hpp>
#include <iostream>

MouseEngine::MouseEngine(Window* window) : window_{window}
{
    glfwSetCursorPosCallback(window_->getWindow(), mouse_position_callback);
    glfwSetMouseButtonCallback(window_->getWindow(), mouse_button_callback);
    glfwSetScrollCallback(window_->getWindow(), scroll_callback);
}

void MouseEngine::mouse_position_callback([[maybe_unused]] GLFWwindow *window, double xpos, double ypos)
{
    mousePos = {xpos, ypos};
}

void MouseEngine::mouse_button_callback([[maybe_unused]]GLFWwindow *window, int button, int action, [[maybe_unused]]int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        mouseReleased = false;
    }
    else
    {
        mouseReleased = true;
    }
}

void MouseEngine::scroll_callback([[maybe_unused]]GLFWwindow *window, [[maybe_unused]]double xoffset, double yoffset)
{
    // Imprime el desplazamiento de la rueda del ratón
    mouseWheel = static_cast<float>(yoffset);
}

glm::vec2 MouseEngine::getPosition()
{
    return mousePos;
}

bool MouseEngine::isMouseReleased()
{
    return mouseReleased;
}

bool MouseEngine::isMouseButtonPressed(GLFWwindow *window, int button)
{
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

float MouseEngine::getMouseWheelMove()
{
    return mouseWheel;
}