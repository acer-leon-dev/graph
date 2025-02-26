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

// May return NaN
math::number example_function(math::number x) {
    return std::pow(math::constant::e, x); 
}
 
sf::Vector2f mapPointToScreen(const sf::Vector2f& point, const sf::Vector2f& domain, const sf::Vector2f& range, float width, float height) {
    return { 
        width * point.x / (domain.y - domain.x), 
        height * (-1 * point.y / (range.y - range.x) + .5f)
    };
}

std::vector<sf::Vector2f> mapGraphToScreenAndGetData(math::Graph& g) {
    std::vector<sf::Vector2f> res;
    const auto& points = g.get_data();
    res.reserve(points.size());
    for (const auto& p : points) {
        res.push_back(mapPointToScreen(
            static_cast<sf::Vector2f>(p), 
            static_cast<sf::Vector2f>(g.get_domain()), 
            static_cast<sf::Vector2f>(g.get_range()),
            800, 600
        ));
    }
    return std::move(res);
}

void drawLine(sf::RenderWindow &window, sf::Vector2i point1, sf::Vector2i point2, int lineWidth, sf::Color lineColor)
{
    int x0 = point1.x;
    int y0 = point1.y;
    int x1 = point2.x;
    int y1 = point2.y;
    int dx = abs(x1 - x0);
    int sx, sy;
    if (x0 < x1) {
        sx = 1;
    }
    else {
        sx = -1;
    }

    int dy = -abs(y1 - y0);
    if (y0 < y1) {
        sy = 1;
    }
    else {
        sy = -1;
    }

    int err = dx + dy;

    while (true) {
        sf::RectangleShape rect(sf::Vector2f(lineWidth, lineWidth));
        rect.setFillColor(lineColor);
        rect.setPosition({(float)x0, (float)y0});
        window.draw(rect);
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * err;

        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void drawPointsSequence(const std::vector<sf::Vector2f>& points, sf::RenderWindow &window) {
    int right = 1;
    for (int left = 0; left < points.size() - 1; left++) {
        if (std::isnan(points[right].y)) {
            right++;
            continue;
        }

        drawLine(window, 
            static_cast<sf::Vector2i>(points[left]), 
            static_cast<sf::Vector2i>(points[right]),
            3, sf::Color(0x4452f2));
        right++;
    }
}


int main(int argc, char* argv[])
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Graphing App");

    math::Graph graph{{-2 * math::constant::pi, 2 * math::constant::pi}, 500, example_function};
    auto newPoints = mapGraphToScreenAndGetData(graph);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
 
        // Clear screen
        window.clear();

        drawPointsSequence(newPoints, window);
        
        window.display();
        
    }
}