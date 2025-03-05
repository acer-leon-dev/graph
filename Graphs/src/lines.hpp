#pragma once

#include "pch.hpp"

void drawLine(sf::RenderTarget& target, sf::Vector2f point1, sf::Vector2f point2, sf::Color color, int weight, bool antialiased = true);
void drawLines(sf::RenderTarget& target, sf::Color color, int weight, bool antialiased, const std::vector<sf::Vector2f>& points);

class LinesLegacy : public sf::Drawable
{
public:
    LinesLegacy();
    LinesLegacy(const std::vector<sf::Vector2f>& points);

    void setPoints(const std::vector<sf::Vector2f>& points);
    const std::vector<sf::Vector2f>& getPoints() const;

    void setColor(sf::Color color);
    sf::Color getColor() const;
    
    void setAntialiased(bool antialiased);
    bool getAntialiased() const;

    void setWeight(int weight);
    int getWeight() const;
private:
    bool m_antialiased;
    sf::Color m_color;
    int m_weight;
    std::vector<sf::Vector2f> m_points;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class Lines // : public sf::Drawable
{
public:
    Lines(sf::Texture& texture, const std::vector<sf::Vector2u>& points);
    void updateTexture();

    sf::Texture& getTexture();

    void setPoints(const std::vector<sf::Vector2u>& points);
    const std::vector<sf::Vector2u>& getPoints() const;

    void setColor(sf::Color color);
    sf::Color getColor() const;
    
    void setWeight(int weight);
    int getWeight() const;
    
    // void setAntialiased(bool antialiased);
    // bool getAntialiased() const;
private:
    // bool m_antialiased;
    sf::Texture m_texture;
    sf::Color m_color;
    int m_weight;

    unsigned int m_width;
    unsigned int m_height;
    std::vector<uint8_t> m_pixels;
    std::vector<sf::Vector2u> m_points;
    // void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};