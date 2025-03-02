#include "Timer.hpp"

FrameTimer::FrameTimer() {
    m_internal_clock.start();
}

void FrameTimer::tick(float seconds)
{
    while (m_internal_clock.getElapsedTime().asSeconds() < seconds)
    {

    }

    m_internal_clock.restart();
}