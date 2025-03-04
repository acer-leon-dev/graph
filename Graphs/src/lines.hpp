#pragma once

#include <SFML/Graphics.hpp>

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

class Lines : public sf::Drawable
{
public:
    Lines(sf::Vector2i domain, sf::Vector2i range);
    Lines(const std::vector<sf::Vector2i>& points, sf::Vector2i domain, sf::Vector2i range);
    void update();

    void setPoints(const std::vector<sf::Vector2i>& points);
    const std::vector<sf::Vector2i>& getPoints() const;

    void setColor(sf::Color color);
    sf::Color getColor() const;
    
    void setWeight(int weight);
    int getWeight() const;
    
    // void setAntialiased(bool antialiased);
    // bool getAntialiased() const;
private:
    // bool m_antialiased;
    sf::Color m_color;
    int m_weight;

    int m_width;
    int m_height;
    std::vector<sf::Vector2i> m_points;
    std::vector<uint8_t> m_pixels;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};