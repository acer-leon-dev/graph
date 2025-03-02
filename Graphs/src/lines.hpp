#ifndef E6DCCC6B_0DA8_49CE_9C1E_362557A16E1E
#define E6DCCC6B_0DA8_49CE_9C1E_362557A16E1E

#include <SFML/Graphics.hpp>

void drawLine(sf::RenderWindow &window, sf::Vector2f point1, sf::Vector2f point2, sf::Color color, int thickness, bool antialiased = true);
void drawLines(sf::RenderWindow &window, const std::vector<sf::Vector2f>& points);

#endif /* E6DCCC6B_0DA8_49CE_9C1E_362557A16E1E */
