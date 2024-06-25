#pragma once
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace vx
{
    class Window;

    class WindowEvents
    {
    public:
        struct InputState;

        static void init(vx::Window* window);
        static void pull();
        static void lastUpdate();
        static InputState getKeyboardKeyState(const int32_t key);
        static InputState getMouseButtonState(const int32_t button);
        static glm::vec2 getMousePosition();
        static glm::vec2 getDeltaMousePosition();

        struct InputState
        {
            bool isPressed;
            bool isHolding;
        };

    private:
        static std::unordered_map<int32_t, InputState> _keyboardStates;
        static std::unordered_map<int32_t, InputState> _mouseStates;

        static glm::vec2 _mousePosition;
        static glm::vec2 _mouseDeltaPosition;
        static bool _mouseStarted;

        static Window* _window;
    };
}
