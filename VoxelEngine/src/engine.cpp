#include "engine.hpp"
#include "deltatime.hpp"

vx::Engine::Engine(const std::string& windowTitle)
{
    _window = new Window();
    _window->init(1200, 800, windowTitle);
}

vx::Engine::~Engine()
{
}

void vx::Engine::start()
{
    onStart();

    while (!_window->isShouldClose())
    {
        _window->pullEvents();

        update();
        render();
    }
}

void vx::Engine::update()
{
    DeltaTime::update();
    onUpdate();
    _window->lastUpdateEvents();
}

void vx::Engine::render()
{
    onRender();
    _window->swapBuffers();
}
