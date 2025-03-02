#pragma once

#include <SFML/System.hpp>

class FrameTimer
{
public:
    FrameTimer();

    void tick(float seconds);

private:
    sf::Clock m_internal_clock;
};