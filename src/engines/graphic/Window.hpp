#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

const unsigned int SCR_WIDTH  {1920};
const unsigned int SCR_HEIGTH {1080};

struct Window
{
    void init(std::string windowName, unsigned int width, unsigned int heigth, bool fullScreen);
    GLFWwindow *getWindow();
    int getWidth();
    int getHeigth();
    void resizeWindow(unsigned int width, unsigned int heigth);
    void postRender();
    static void framebuffer_size_callback(GLFWwindow *window, int width, int heigth);

    private:
        GLFWwindow *window_;
        int width_, heigth_;
};

GLFWmonitor* glfwGetActiveMonitor(GLFWwindow* window);