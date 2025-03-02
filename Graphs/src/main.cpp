#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <iterator>
#include <algorithm>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "math.hpp"
#include "mapping.hpp"
#include "lines.hpp"

struct SCREEN
{
    static inline constexpr int WIDTH = 1600;
    static inline constexpr int HEIGHT = 900;
    static inline constexpr sf::Vector2f SIZE{WIDTH, HEIGHT};
    static inline constexpr int FPS = 60;
    static inline constexpr float TICKPERFRAME = 1000 / FPS;
};
 
sf::Vector2f mapPointToScreen(const sf::Vector2f& point, const sf::Vector2f& domain, const sf::Vector2f& range, float width, float height)
{
    return {
        width * point.x / (domain.y - domain.x), 
        height * (-1 * point.y / (range.y - range.x) + .5f)
    };
}

std::vector<sf::Vector2f> mapGraphToScreenAndGetData(math::Graph& g)
{
    std::vector<sf::Vector2f> res;
    const auto& points = g.get_data();
    res.reserve(points.size());
    for (const auto& p : points)
    {
        res.push_back(mapPointToScreen(
            static_cast<sf::Vector2f>(p), 
            static_cast<sf::Vector2f>(g.get_domain()), 
            static_cast<sf::Vector2f>(g.get_range()),
            800, 600
        ));
    }
    return res;
}

math::number exampleFunction(math::number x)
{
    return std::sin(x); 
}

int main(int argc, char* argv[])
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({SCREEN::WIDTH, SCREEN::HEIGHT}), "Graphs");

    // Create graph object
    math::number low = -2 * math::constant::pi;
    math::number high = 2 * math::constant::pi;
    math::Graph graph{{low, high}, 500, exampleFunction};
    auto newPoints = mapGraphToScreenAndGetData(graph);
    
    while (window.isOpen()) {
        ///// Handling Events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        //// Drawing
        window.clear();
        
        // Draw graph
        drawLines(window, newPoints);


        //// Misc

        window.display();
        
    }
}