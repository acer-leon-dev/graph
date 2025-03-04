#include "pch.hpp"

#include <vector>
#include <format>

#include "Generators.hpp"
#include "Graph.hpp"
#include "Lines.hpp"
#include "Timer.hpp"
#include "systemfont.hpp"

struct Screen
{
    static inline constexpr int WIDTH = 1600;
    static inline constexpr int HEIGHT = 900;
    static inline constexpr sf::Vector2f SIZE{WIDTH, HEIGHT};
    static inline constexpr int FPS = 120;
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
    const std::vector<sf::Vector2<double>>& in_points = graph.getPoints();
    std::vector<sf::Vector2<T>> out_pixels;

    out_pixels.reserve(in_points.size());
    std::transform(
        in_points.begin(), in_points.end(),
        std::back_inserter(out_pixels),
        [&](sf::Vector2<double> value) { 
            return static_cast<sf::Vector2<T>>(
                graphPointToPixel(
                    target, 
                    static_cast<sf::Vector2f>(value),
                    graph
                )
            ); 
        }      
    );

    return out_pixels;
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
    GraphScaler(double domain_factor, double range_factor, double subint_change) 
    :   domain_factor{domain_factor}, 
        range_factor{range_factor},
        subint_change{subint_change},
        subints_increasing{false},
        subints_decreasing{false},
        domain_increasing{false},
        domain_decreasing{false},
        range_increasing{false},
        range_decreasing{false}
    {

    }

    void update(Graph& graph) 
    {
        // Domain
        auto domain = graph.getDomain();
        if (domain_increasing) {
            domain = domain.componentWiseMul({domain_factor, domain_factor});
        }
        if (domain_decreasing) {
            domain = domain.componentWiseDiv({domain_factor, domain_factor});
        }

        // Range
        auto function = graph.getFunction();
        if (range_increasing) {
            function = [function, this](double x){ return function(x) * domain_factor; };
        }
        if (range_decreasing) {
            function = [function, this](double x){ return function(x) / domain_factor; };
        }

        // Subints
        int subints = graph.getSubintervals();
        if (subints_increasing) {
            subints = std::round(subints + subint_change);
        }
        if (subints_decreasing) {
            subints = std::max(1.0, std::round(subints - subint_change));
        }

        graph.update(domain, function, subints);
    }
public:
    double domain_factor;
    double range_factor;
    double subint_change;
    bool subints_increasing;
    bool subints_decreasing;
    bool domain_increasing;
    bool domain_decreasing;
    bool range_increasing;
    bool range_decreasing;
};

int main(int argc, char* argv[])
{
    // Create the main window and a timer
    sf::RenderWindow window(sf::VideoMode({Screen::WIDTH, Screen::HEIGHT}), "Graphs");
    FrameTimer timer;
    double deltatime;

    sf::Font gfont{findSystemFont("arial.ttf")};
    FpsCounter fpscounter{
        timer,
        [&]() {
            sf::Text t{gfont};
            t.setCharacterSize(20);
            t.setFillColor(sf::Color::White);
            return t;
        }()
    };

    // Create graph object
    double low = -4 * Constant::pi;
    double high = 4 * Constant::pi;
    Graph graph{{low, high}, exampleFunction, 250};
    
    // Create lines object to represent graph
    // LinesLegacy linesl{pointsToPixels<float>(window, graph)};
    // linesl.setColor(sf::Color(0x4452f2));
    // linesl.setAntialiased(false);
    // linesl.setWeight(1);
    
    sf::Texture tex_lines{window.getSize()};
    Lines lines{tex_lines, pointsToPixels<unsigned int>(window, graph)};
    lines.setColor(sf::Color(0x0abf00ff));
    lines.setWeight(3);
    lines.updateTexture();
    sf::Sprite spr_lines{tex_lines};
    // std::vector<uint8_t> buff(tex_lines.getSize().x * tex_lines.getSize().x * 4, 128);
    // tex_lines.update(buff.data());
    
    sf::Text graph_data_text{gfont, "", 20};
    updateGraphDataText(graph_data_text, graph);
    graph_data_text.setPosition({0, 20});
    
    GraphScaler graph_scaler{1.1, 1.1, 1};

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

                if (p_keypress->scancode == sf::Keyboard::Scancode::Left)
                {
                    graph_scaler.domain_decreasing = true;
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Right)
                {
                    graph_scaler.domain_increasing = true;
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Up)
                {
                    graph_scaler.subints_increasing = true;
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Down)
                {
                    graph_scaler.subints_decreasing = true;
                }
            } 

            if (auto p_keypress = event->getIf<sf::Event::KeyReleased>())
            {
                if (p_keypress->scancode == sf::Keyboard::Scancode::Left)
                {
                    graph_scaler.domain_decreasing = false;
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Right)
                {
                    graph_scaler.domain_increasing = false;
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Up)
                {
                    graph_scaler.subints_increasing = false;
                }

                if (p_keypress->scancode == sf::Keyboard::Scancode::Down)
                {
                    graph_scaler.subints_decreasing = false;
                }
            }
        }
        
        fpscounter.update();
        graph_scaler.update(graph);
        updateGraphDataText(graph_data_text, graph);
        // linesl.setPoints(pointsToPixels<float>(window, graph));
        lines.setPoints(pointsToPixels<unsigned int>(window, graph));
        lines.updateTexture();
        
        //// Drawing

        window.clear();
        
        // window.draw(linesl);
        
        window.draw(spr_lines);
        window.draw(fpscounter);
        window.draw(graph_data_text);        

        //// Misc

        window.display();
        
        deltatime = timer.tick(Screen::TICK);
    }
}