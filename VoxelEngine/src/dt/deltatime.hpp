#pragma once
#include <ctime>
#include <GLFW/glfw3.h>

namespace vx
{
    class DeltaTime
    {
    public:
        static void update();
        static double getDt();

    private:
        static double _prevTime;
        static double _dt;
    };
}
