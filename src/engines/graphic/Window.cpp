#include <GLAD/src/glad.h>
#include <engines/graphic/Window.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/src/stb_image.h>

void Window::init(std::string windowName, unsigned int width, unsigned int heigth, bool fullScreen)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    if (width == 0 || heigth == 0)
    {
        GLFWvidmode const *mode = glfwGetVideoMode(monitor);
        width = mode->width;
        heigth = mode->height;
    }

    if (!fullScreen)
        monitor = nullptr;

    window_ = glfwCreateWindow(width, heigth, windowName.c_str(), monitor, NULL);
    // glfwSetWindowSize(window_, 1280,720);
    if (window_ == NULL)
    {
        glfwTerminate();
    }
    glfwMakeContextCurrent(window_);

    // VSync Enabled
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

    }

    stbi_set_flip_vertically_on_load(true);
    // configure global opengl state
    // -----------------------------
    // Cosas que estan delante tapan a las detras
    glEnable(GL_DEPTH_TEST);
    // Pantalla mismo tamaño cosas de pantalla efectos especiales
    glEnable(GL_STENCIL_TEST);
    // glEnable(GL_CULL_FACE);
    //  Para que pase el color luz a los objetos semitransparentes
    glEnable(GL_BLEND);
    // Fusiona los colores
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glfwGetWindowSize(window_, &width_, &heigth_);
}

void Window::postRender()
{
    glfwSwapBuffers(window_);
    // Cuando pase algo en la ventana llame a los callbacks
    glfwPollEvents();
}

void Window::framebuffer_size_callback([[maybe_unused]]GLFWwindow *window, int width, int heigth)
{
    // Adapta el viewport que la pantalla este en el centro
    glViewport(0, 0, width, heigth);
}

void Window::resizeWindow(unsigned int width, unsigned int heigth)
{
    GLFWmonitor* monitor = glfwGetActiveMonitor(window_);

    width_ = width;
    heigth_ = heigth;

    int x_m{}, y_m{}, width_m{}, height_m{};
    glfwGetMonitorWorkarea(monitor, &x_m, &y_m, &width_m, &height_m);
    if((int)width > width_m || (int)heigth > height_m){
        width = width_m;
        heigth = height_m;
    }
    glfwSetWindowSize(window_, width, heigth);
}

GLFWwindow *Window::getWindow()
{
    return window_;
}

int Window::getWidth()
{
    return width_;
}

int Window::getHeigth()
{
    return heigth_;
}

GLFWmonitor* glfwGetActiveMonitor(GLFWwindow* window){
    int x_window{}, y_window{}, width_window{}, height_window{};
    int x_monitor{}, y_monitor{}, width_monitor{}, height_monitor{};

    int overlap{}, best_overlap{};
    GLFWvidmode const* mode{};
    GLFWmonitor* active_monitor{glfwGetPrimaryMonitor()};
    
    int monitors_size{};
    GLFWmonitor** monitors = glfwGetMonitors(&monitors_size);

    glfwGetWindowPos(window, &x_window, &y_window);
    glfwGetWindowSize(window, &width_window, &height_window);

    for(size_t i{0};i<(size_t)monitors_size;++i){
        // GET the VideoMode of the monitor to get the width and height
        mode = glfwGetVideoMode(monitors[i]);

        // Get the position of the monitor in the global screens scope
        glfwGetMonitorPos(monitors[i], &x_monitor, &y_monitor);

        // Get the monitor dimensions
        width_monitor = mode->width;
        height_monitor = mode->height;

        overlap = std::max(0, std::min(x_window + width_window, x_monitor  + width_monitor)  - std::max(x_window, x_monitor)) * 
                  std::max(0, std::min(y_window + height_window, y_monitor + height_monitor) - std::max(y_window, y_monitor));

        if(best_overlap < overlap){
            best_overlap = overlap;
            active_monitor = monitors[i];
        }

    }

    return active_monitor;

}
