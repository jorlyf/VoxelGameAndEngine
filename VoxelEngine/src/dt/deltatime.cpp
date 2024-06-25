#include "deltatime.hpp"

double vx::DeltaTime::_prevTime = 0.0;
double vx::DeltaTime::_dt = 0.0;

void vx::DeltaTime::update()
{
    const double now = glfwGetTime();
    _dt = now - _prevTime;
    _prevTime = now;
}

double vx::DeltaTime::getDt()
{
    return _dt;
}