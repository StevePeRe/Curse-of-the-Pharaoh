#pragma once

#include <glm/glm.hpp>
#include <engines/graphic/Window.hpp>

struct MouseEngine
{
    MouseEngine(Window* window);

    void static mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
    void static mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void static scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


    glm::vec2 getPosition();
    float getMouseWheelMove();
    void resetMouseWheel() { mouseWheel = 0.0f; }
    bool isMouseReleased();
    bool isMouseButtonPressed(GLFWwindow* window, int button);

    private:
        Window *window_;
        static inline glm::vec2 mousePos{0,0};
        static inline float mouseWheel{0.0f};
        static inline bool mouseReleased{false};
};