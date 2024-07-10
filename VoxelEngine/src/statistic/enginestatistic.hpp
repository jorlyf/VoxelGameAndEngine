#pragma once

namespace vx
{
    class EngineStatistic
    {
    public:
        static double getChunksGenerationTime();
        static double getChunksRenderTime();

        static void updateChunksGenerationTime(const double time);
        static void updateChunksRenderTime(const double time);

    private:
        static double _prevChunksGenerationTime;
        static double _chunksGenerationTime;

        static double _prevChunksRenderTime;
        static double _chunksRenderTime;
    };
}
