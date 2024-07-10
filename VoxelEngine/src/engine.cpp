#include <stdexcept>
#define GLT_IMPLEMENTATION
#include <gltext.h>
#include "engine.hpp"
#include "deltatime.hpp"
#include "enginestatistic.hpp"

vx::Engine::Engine(const std::string& windowTitle)
{
    _window = new Window();
    _window->init(1200, 800, windowTitle);

    if (!gltInit())
    {
        throw std::runtime_error("Failed to initialize glText");
    }
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
    renderStatistics();
    _window->swapBuffers();
}

void vx::Engine::renderStatistics()
{
    GLTtext* text = gltCreateText();
    const std::string chunkGenerationTimeString = "Chunk generation time: " + std::to_string(EngineStatistic::getChunksGenerationTime() * 1000.0);
    gltSetText(text, chunkGenerationTimeString.c_str());

    gltBeginDraw();

    gltDrawText2D(text, 0.0f, 0.0f, 1.0f);

    gltEndDraw();
}
