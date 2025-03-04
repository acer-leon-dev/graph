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
#include "Lines.hpp"
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

sf::View getViewFromGraph(const math::Graph& graph)
{
    return {
        {0, 0}, 
        { static_cast<float>(graph.getWidth()),
        static_cast<float>(graph.getHeight()) }
    };
}

template<class T> sf::Vector2<T> graphPointToPixel(sf::RenderTarget& target, const sf::Vector2<T>& point, const math::Graph& graph)
{
    return static_cast<sf::Vector2<T>>(target.mapCoordsToPixel({point.x, point.y * -1}, getViewFromGraph(graph)));
}


std::vector<sf::Vector2f> pointsToPixels(sf::RenderTarget& target, const math::Graph& graph)
{
    const auto& points = graph.getPoints();
    std::vector<sf::Vector2f> pixels;
    pixels.reserve(points.size());
    for (sf::Vector2<double> point : points)
    {
        sf::Vector2f newp = static_cast<sf::Vector2f>(graphPointToPixel(target, static_cast<sf::Vector2f>(point), graph));
        pixels.push_back(newp);
    }
    return pixels;
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
    math::Graph graph{{low, high}, exampleFunction, 500};
    
    // for (auto p : graph.getPoints())
    // {
    //     std::cout << "{" << p.x << ", " << p.y << "} ";
    // }

    
    // Create lines object to represent graph
    LinesLegacy linesl{pointsToPixels(window, graph)};
    linesl.setColor(sf::Color(0x4452f2));
    linesl.setAntialiased(false);
    linesl.setWeight(1);
    
    
    // Lines lines{
    //     static_cast<sf::Vector2i>(graph.getDomain()), 
    //     static_cast<sf::Vector2i>(graph.getRange())
    // };
    // lines.setPoints([&graph](){
    //     const std::vector<sf::Vector2<double>>& pointsf = graph.getPoints(); 
    //     std::vector<sf::Vector2i> pointsi;
    //     pointsi.reserve(pointsf.size());
        
    //     for (auto p : pointsf)
    //     {
    //         pointsi.push_back(static_cast<sf::Vector2i>(p));
    //     }
    
    //     return pointsi;
    // }());
    // lines.setColor(sf::Color(0x0abf00ff));
    // lines.setWeight(3);

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
                if (p_keypress->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
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
                    auto d = graph.getDomain().componentWiseDiv({1.1, 1.1});
                    auto f = graph.getFunction();
                    graph.update(d, f, 250);
                    linesl.setPoints(pointsToPixels(window, graph));
                    updateGraphDataText(graph_data_text, graph);
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Right)
                {
                    auto d = graph.getDomain().componentWiseMul({1.1, 1.1});
                    auto f = graph.getFunction();
                    graph.update(d, f, 250);
                    linesl.setPoints(pointsToPixels(window, graph));
                    updateGraphDataText(graph_data_text, graph);
                }
            } 
        }
        
        //// Drawing

        window.clear();
        
        window.draw(linesl);
        // window.draw(lines);
        
        fpscounter.update();
        window.draw(fpscounter);
        window.draw(graph_data_text);
        
        //// Misc

        window.display();
        
        timer.tick(Screen::TICK);
    }
}