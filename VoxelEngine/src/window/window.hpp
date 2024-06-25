#pragma once
#include <stdint.h>
#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace vx
{
    class Window
    {
    public:
        void init(
            const uint32_t width,
            const uint32_t height,
            const std::string& title
        );
        void pullEvents();
        void lastUpdateEvents();
        void swapBuffers();
        void terminate();
        void setIsCursorVisible(const bool isVisible);
        bool isShouldClose();
        void onResize(const uint32_t width, const uint32_t height);
        std::string getTitle() const;
        void setTitle(const std::string& title);
        GLFWwindow* getGLFWwindow() const;
        glm::u32vec2 getSize() const;

    private:
        GLFWwindow* _window = nullptr;

        uint32_t _width, _height;
        std::string _title;

        bool _isCursorVisible = true;

        void initEvents();
    };
}
