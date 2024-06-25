#include <stdexcept>
#include <GL/glew.h>
#include "window.hpp"
#include "windowevents.hpp"

void vx::Window::init(const uint32_t width, const uint32_t height, const std::string& title)
{
    _width = width;
    _height = height;
    _title = title;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    if (_window == nullptr)
    {
        terminate();
        throw std::runtime_error("Failed to create glfw window");
    }

    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    const int32_t status = glewInit();
    // if (status != GLEW_OK)
    // {
    //     terminate();
    //     throw std::runtime_error("Failed to init glew");
    // }

    onResize(_width, _height);

    initEvents();
    setIsCursorVisible(false);
}

void vx::Window::pullEvents()
{
    WindowEvents::pull();
}

void vx::Window::lastUpdateEvents()
{
    WindowEvents::lastUpdate();
}

void vx::Window::swapBuffers()
{
    glfwSwapBuffers(_window);
}

void vx::Window::terminate()
{
    glfwTerminate();
}

void vx::Window::setIsCursorVisible(const bool isVisible)
{
    _isCursorVisible = isVisible;
    const int32_t mode = _isCursorVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
    glfwSetInputMode(_window, GLFW_CURSOR, mode);
}

bool vx::Window::isShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void vx::Window::onResize(const uint32_t width, const uint32_t height)
{
    _width = width;
    _height = height;

    glViewport(0, 0, _width, _height);
}

std::string vx::Window::getTitle() const
{
    return _title;
}

void vx::Window::setTitle(const std::string& title)
{
    _title = title;
    glfwSetWindowTitle(_window, _title.c_str());
}

GLFWwindow* vx::Window::getGLFWwindow() const
{
    return _window;
}

glm::u32vec2 vx::Window::getSize() const
{
    return glm::u32vec2(_width, _height);
}

void vx::Window::initEvents()
{
    WindowEvents::init(this);
}
