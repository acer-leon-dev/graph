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

sf::View getViewFromGraph(const Graph& graph)
{
    return {
        {0, 0}, 
        { static_cast<float>(graph.getWidth()),
        static_cast<float>(graph.getHeight()) }
    };
}

sf::Vector2i graphPointToPixel(sf::RenderTarget& target, const sf::Vector2f& point, const Graph& graph)
{
    return target.mapCoordsToPixel({point.x, point.y * -1}, getViewFromGraph(graph));
}

template<class T> std::vector<sf::Vector2<T>> pointsToPixels(sf::RenderTarget& target, const Graph& graph)
{
    const auto& points = graph.getPoints();
    std::vector<sf::Vector2<T>> pixels;
    pixels.reserve(points.size());
    for (sf::Vector2<double> point : points)
    {
        sf::Vector2<T> newp = static_cast<sf::Vector2<T>>(graphPointToPixel(target, static_cast<sf::Vector2f>(point), graph));
        pixels.push_back(newp);
    }
    return pixels;
}

void updateGraphDataText(sf::Text& text, Graph& graph)
{
    double d1 = std::round(graph.getDomain().x * 1000) / 1000;
    double d2 = std::round(graph.getDomain().y * 1000) / 1000;
    double r1 = std::round(graph.getRange().x * 1000) / 1000;
    double r2 = std::round(graph.getRange().y * 1000) / 1000;
    int subints = graph.getSubintervals();
    text.setString(std::format(
        "Dom: {{{}, {}}}\nRan: {{{}, {}}}\nSubints: {}", 
        d1, d2, r1, r2, subints)
    );
}

double exampleFunction(double x)
{
    return std::sin(x); 
}

struct GraphScaler
{
public:
    GraphScaler(Graph& graph, double factor) : graph{graph}, factor{factor}, expanding{false}, shrinking{false}
    {

    }

    void update() {
        auto d = graph.getDomain();

        if (expanding)
        {
            d = d.componentWiseMul({1.1, 1.1});
        }

        if (shrinking)
        {
            d = d.componentWiseDiv({1.1, 1.1});
        }

        auto f = graph.getFunction();
        graph.update(d, f, 250);
    }
public:
    Graph& graph;
    double factor;
    bool expanding;
    bool shrinking;
};

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
    double low = -4 * Constant::pi;
    double high = 4 * Constant::pi;
    Graph graph{{low, high}, exampleFunction, 250};
    
    // for (auto p : graph.getPoints())
    // {
    //     std::cout << "{" << p.x << ", " << p.y << "} ";
    // }

    
    // Create lines object to represent graph
    LinesLegacy linesl{pointsToPixels<float>(window, graph)};
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
    
    GraphScaler graph_scaler{graph, 1.1};

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
                    graph_scaler.shrinking = true;
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Right)
                {
                    graph_scaler.expanding = true;
                }
            } 

            if (auto p_keypress = event->getIf<sf::Event::KeyReleased>())
            {
                if (p_keypress->scancode == sf::Keyboard::Scancode::Left)
                {
                    graph_scaler.shrinking = false;
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Right)
                {
                    graph_scaler.expanding = false;
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
        
        graph_scaler.update();
        linesl.setPoints(pointsToPixels<float>(window, graph));
        updateGraphDataText(graph_data_text, graph);

        //// Misc

        window.display();
        
        timer.tick(Screen::TICK);
    }
}