#pragma once
#include "window/window.hpp"

namespace vx
{
    class Engine
    {
    public:
        Engine(const std::string& windowTitle);
        virtual ~Engine();

        void start();
        void update();
        void render();

        virtual void onStart() = 0;
        virtual void onUpdate() = 0;
        virtual void onRender() = 0;

    protected:
        Window* _window = nullptr;
    };
}
