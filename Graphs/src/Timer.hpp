#pragma once

#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////////////////////////

class FrameTimer
{
public:
    FrameTimer();
    double tick(double seconds);
    double fps();
    double dt();
private:
    double m_dt;
    double m_time_last_tick;
    double m_counted_frames;
    sf::Clock m_tick_clock;
    sf::Clock m_counter_clock;
};

////////////////////////////////////////////////////////////////////////////////

class FpsCounter : public sf::Drawable
{
public:
    FpsCounter(FrameTimer& timer, const sf::Text& text);
    void update();
    void copyStyle(const sf::Text& text);
    const sf::Text& getText();
private:
    FrameTimer& m_timer;
    sf::Text m_text;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};