#pragma once

#include <SFML/Graphics.hpp>

void drawLine(sf::RenderTarget& target, sf::Vector2f point1, sf::Vector2f point2, sf::Color color, int thickness, bool antialiased = true);
void drawLines(sf::RenderTarget& target, sf::Color color, int thickness, bool antialiased, const std::vector<sf::Vector2f>& points);

class Lines : public sf::Drawable
{
public:
    Lines();
    Lines(const std::vector<sf::Vector2f>& points);

    void setPoints(const std::vector<sf::Vector2f>& points);
    const std::vector<sf::Vector2f>& getPoints() const;

    void setColor(sf::Color color);
    sf::Color getColor() const;
    
    void setThickness(int thickness);
    int getThickness() const;
    
    void setAntialiased(bool antialiased);
    bool getAntialiased() const;
private:
    std::vector<sf::Vector2f> m_points;
    sf::Color m_color;
    int m_thickness;
    bool m_antialiased;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};