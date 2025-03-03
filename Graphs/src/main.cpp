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
#include "lines.hpp"
#include "Timer.hpp"
#include "systemfont.hpp"

struct SCREEN
{
    static inline constexpr int WIDTH = 1600;
    static inline constexpr int HEIGHT = 900;
    static inline constexpr sf::Vector2f SIZE{WIDTH, HEIGHT};
    static inline constexpr int FPS = 60;
    static inline constexpr float TICK = 1.0f / FPS;
};
 
float inverselerp(float x, float a, float b)
{
    return (x - a) / (b - a);
}

sf::Vector2f scalePoint(const sf::Vector2f& point, const sf::Vector2f& domain, const sf::Vector2f& range, float width, float height)
{
    return {
        width * inverselerp(point.x, domain.x, domain.y), 
        height * (1 - inverselerp(point.y, range.x, range.y))
    };
}

std::vector<sf::Vector2f> mapGraphToScreenAndGetData(math::Graph& g)
{
    std::vector<sf::Vector2f> res;
    const auto& points = g.get_data();
    res.reserve(points.size());
    for (const auto& p : points)
    {
        res.push_back(scalePoint(
            static_cast<sf::Vector2f>(p), 
            static_cast<sf::Vector2f>(g.get_domain()), 
            static_cast<sf::Vector2f>(g.get_range()),
            SCREEN::WIDTH, SCREEN::HEIGHT
        ));
    }
    return res;
}

math::number exampleFunction(math::number x)
{
    return std::tan(x); 
}

int main(int argc, char* argv[])
{
    // Create the main window and a timer
    sf::RenderWindow window(sf::VideoMode({SCREEN::WIDTH, SCREEN::HEIGHT}), "Graphs");
    FrameTimer timer;
    
    sf::Font font{findSystemFont("arial.ttf")};
    FpsCounter fpscounter{
        timer,
        [&]() {
            sf::Text t{font};
            t.setCharacterSize(30);
            t.setFillColor(sf::Color::White);
            return t;
        }()
    };

    // Create graph object
    math::number low = -4 * math::constant::pi;
    math::number high = 4 * math::constant::pi;
    math::Graph graph{{low, high}, 1000, exampleFunction};
    
    // Create lines object to represent graph
    Lines lines{mapGraphToScreenAndGetData(graph)};
    lines.setColor(sf::Color(0x4452f2));
    lines.setAntialiased(true);
    lines.setThickness(3);

    while (window.isOpen()) {
        //// Handling Events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        //// Drawing

        window.clear();
        
        // Draw graph
        //  Old Method:
        // drawLines(window, sf::Color(0xFFFFFFFF), 5, false, newPoints);
        //  New method:
        window.draw(lines);

        fpscounter.update();
        window.draw(fpscounter);
        
        //// Misc

        window.display();
        
        timer.tick(SCREEN::TICK);
    }
}