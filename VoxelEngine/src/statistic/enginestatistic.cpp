#include <GLFW/glfw3.h>
#include "enginestatistic.hpp"

double vx::EngineStatistic::_prevChunksGenerationTime = 0.0;
double vx::EngineStatistic::_chunksGenerationTime = 0.0;

double vx::EngineStatistic::_prevChunksRenderTime = 0.0;
double vx::EngineStatistic::_chunksRenderTime = 0.0;

double vx::EngineStatistic::getChunksGenerationTime()
{
    return _chunksGenerationTime;
}

double vx::EngineStatistic::getChunksRenderTime()
{
    return _chunksRenderTime;
}

void vx::EngineStatistic::updateChunksGenerationTime(const double time)
{
    _chunksGenerationTime = time;
}

void vx::EngineStatistic::updateChunksRenderTime(const double time)
{
    _chunksRenderTime = time;
}
