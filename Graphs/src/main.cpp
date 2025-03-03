#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <iterator>
#include <algorithm>
#include <format>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "math.hpp"
#include "lines.hpp"
#include "Timer.hpp"
#include "systemfont.hpp"

struct Screen
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

sf::Vector2f pointToScreen(const sf::Vector2f& point, const sf::Vector2f& domain, const sf::Vector2f& range, sf::Vector2f screensize)
{
    return {
        screensize.x * inverselerp(point.x, domain.x, domain.y), 
        screensize.y * (1 - inverselerp(point.y, range.x, range.y))
    };
}

std::vector<sf::Vector2f> mapGraphToScreenAndGetData(math::Graph& g)
{
    std::vector<sf::Vector2f> res;
    const auto& points = g.getData();
    res.reserve(points.size());
    for (sf::Vector2<double> p : points)
    {
        sf::Vector2f newp = pointToScreen(
            static_cast<sf::Vector2f>(p), 
            static_cast<sf::Vector2f>(g.getDomain()), 
            static_cast<sf::Vector2f>(g.getRange()),
            Screen::SIZE
        );

        res.push_back(newp);
    }
    return res;
}

void updateGraphDataText(sf::Text& text, math::Graph& graph)
{
    double d1 = std::round(graph.getDomain().x * 1000) / 1000;
    double d2 = std::round(graph.getDomain().y * 1000) / 1000;
    double r1 = std::round(graph.getRange().x * 1000) / 1000;
    double r2 = std::round(graph.getRange().y * 1000) / 1000;
    text.setString(std::format(
        "Dom: {{{}, {}}}\nRan: {{{}, {}}}", 
        d1, d2, r1, r2)
    );
}

double exampleFunction(double x)
{
    return std::sin(x); 
}

int main(int argc, char* argv[])
{
    // Create the main window and a timer
    sf::RenderWindow window(sf::VideoMode({Screen::WIDTH, Screen::HEIGHT}), "Graphs");
    FrameTimer timer;
    
    sf::Font font{findSystemFont("arial.ttf")};
    FpsCounter fpscounter{
        timer,
        [&]() {
            sf::Text t{font};
            t.setCharacterSize(20);
            t.setFillColor(sf::Color::White);
            return t;
        }()
    };

    // Create graph object
    double low = -4 * math::Constant::pi;
    double high = 4 * math::Constant::pi;
    math::Graph graph{{low, high}, exampleFunction, 100};
    
    // Create lines object to represent graph
    Lines lines{mapGraphToScreenAndGetData(graph)};
    lines.setColor(sf::Color(0x4452f2));
    lines.setAntialiased(false);
    lines.setThickness(3);

    //
    sf::Text graph_data_text{font, "", 20};
    updateGraphDataText(graph_data_text, graph);
    graph_data_text.setPosition({0, 20});

    // Main loop
    while (window.isOpen())
    {
        //// Handling Events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (auto p_keypress = event->getIf<sf::Event::KeyPressed>())
            {
                if (p_keypress->scancode == sf::Keyboard::Scancode::Up)
                {
            
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Down)
                {
                    
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Left)
                {
                    auto d = graph.getDomain();
                    auto f = graph.getFunction();
                    graph.update(d.componentWiseDiv({1.1, 1.1}), f, 100);
                    lines.setPoints(mapGraphToScreenAndGetData(graph));
                    updateGraphDataText(graph_data_text, graph);
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Right)
                {
                    auto d = graph.getDomain();
                    auto f = graph.getFunction();
                    graph.update(d.componentWiseMul({1.1, 1.1}), f, 100);
                    lines.setPoints(mapGraphToScreenAndGetData(graph));
                    updateGraphDataText(graph_data_text, graph);
                }
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
        window.draw(graph_data_text);
        
        //// Misc

        window.display();
        
        timer.tick(Screen::TICK);
    }
}