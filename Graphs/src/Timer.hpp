#pragma once

#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////////////////////////

class FrameTimer
{
public:
    FrameTimer();

    void tick(float seconds);

    float getFPS();

private:
    float m_fps;
    float m_counted_frames;
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
    sf::Font m_font;
    sf::Text m_text;
    FrameTimer& m_timer;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};