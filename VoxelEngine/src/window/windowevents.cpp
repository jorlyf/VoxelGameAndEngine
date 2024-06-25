#include "windowevents.hpp"
#include "window.hpp"

std::unordered_map<int32_t, vx::WindowEvents::InputState> vx::WindowEvents::_keyboardStates;
std::unordered_map<int32_t, vx::WindowEvents::InputState> vx::WindowEvents::_mouseStates;

glm::vec2 vx::WindowEvents::_mousePosition{};
glm::vec2 vx::WindowEvents::_mouseDeltaPosition{};
bool vx::WindowEvents::_mouseStarted = false;

vx::Window* vx::WindowEvents::_window = nullptr;

void vx::WindowEvents::init(vx::Window* window)
{
    _window = window;
    GLFWwindow* glfwWindow = _window->getGLFWwindow();

    glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, const int32_t key, const int32_t scancode, const int32_t action, const int32_t mode) {
        if (action == GLFW_PRESS)
        {
            WindowEvents::_keyboardStates[key].isPressed = true;
            WindowEvents::_keyboardStates[key].isHolding = true;
        }
        else if (action == GLFW_RELEASE)
        {
            WindowEvents::_keyboardStates[key].isPressed = false;
            WindowEvents::_keyboardStates[key].isHolding = false;
        }
        });
    glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, const int32_t button, const int32_t action, const int32_t mode) {
        if (action == GLFW_PRESS)
        {
            WindowEvents::_mouseStates[button].isPressed = true;
            WindowEvents::_mouseStates[button].isHolding = true;
        }
        else if (action == GLFW_RELEASE)
        {
            WindowEvents::_mouseStates[button].isPressed = false;
            WindowEvents::_mouseStates[button].isHolding = false;
        }
        });
    glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, const double x, const double y) {
        if (_mouseStarted)
        {
            _mouseDeltaPosition.x += _mousePosition.x - x;
            _mouseDeltaPosition.y += _mousePosition.y - y;
        }
        else
        {
            _mouseStarted = true;
        }
        _mousePosition.x = x;
        _mousePosition.y = y;
        });
    glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow* window, const int32_t width, const int32_t height) {
        _window->onResize(width, height);
        });
}

void vx::WindowEvents::pull()
{
    glfwPollEvents();
}

void vx::WindowEvents::lastUpdate()
{
    for (auto& item : _keyboardStates)
    {
        InputState& state = item.second;
        state.isPressed = false;
    }
    for (auto& item : _mouseStates)
    {
        InputState& state = item.second;
        state.isPressed = false;
    }

    _mouseDeltaPosition.x = 0.0f;
    _mouseDeltaPosition.y = 0.0f;
}

vx::WindowEvents::InputState vx::WindowEvents::getKeyboardKeyState(const int32_t key)
{
    return _keyboardStates[key];
}

vx::WindowEvents::InputState vx::WindowEvents::getMouseButtonState(const int32_t button)
{
    return _mouseStates[button];
}

glm::vec2 vx::WindowEvents::getMousePosition()
{
    return _mousePosition;
}

glm::vec2 vx::WindowEvents::getDeltaMousePosition()
{
    return _mouseDeltaPosition;
}
