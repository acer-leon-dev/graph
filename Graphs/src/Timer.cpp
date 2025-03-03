#include "Timer.hpp"
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

FrameTimer::FrameTimer() : m_fps(0) {
    m_tick_clock.start();
    m_counter_clock.start();
}

void FrameTimer::tick(float seconds)
{
    while (m_tick_clock.getElapsedTime().asSeconds() < seconds)
    {

    }
    
    m_fps = 1 / m_tick_clock.getElapsedTime().asSeconds();
    m_tick_clock.restart();
    m_counted_frames++;
}

float FrameTimer::getFPS()
{
    float calculated_average_fps = m_counted_frames / m_counter_clock.getElapsedTime().asSeconds();
    
    if (m_counter_clock.getElapsedTime().asSeconds() > .5)
    {
        m_counter_clock.restart();
        m_counted_frames = 0;
    }

    return calculated_average_fps;
}

////////////////////////////////////////////////////////////////////////////////

FpsCounter::FpsCounter(FrameTimer& timer, const sf::Text& text)
:   m_timer{timer}, m_text(text)
{
    m_text.setString("0");
}

void FpsCounter::update()
{
    float fps = m_timer.getFPS();
    int rounded = std::round(fps);
    m_text.setString(std::to_string(rounded));
}

void FpsCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text);
}

void FpsCounter::copyStyle(const sf::Text& text)
{
    std::string original_string = m_text.getString();
    m_text = text;
    m_text.setString(original_string);
}

const sf::Text& FpsCounter::getText()
{
    return m_text;
}