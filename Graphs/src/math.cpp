#include "math.hpp"
#include <string>
#include <iostream>
#include <algorithm>

namespace math {

Graph::Graph(sf::Vector2<number> d, unsigned int intervals, number (*func)(number))
: m_domain(d)
{
    m_graph.reserve(intervals);
    
    number dif = std::abs((d.y - d.x) / intervals);
    for (number x = d.x; x < d.y - dif / 10; x += dif)
    {
        number y = func(x);
        m_range.x = std::min(m_range.x, y);
        m_range.y = std::max(m_range.y, y);
        m_graph.emplace_back(x, y);
    }
    
    m_graph.emplace_back(d.y, func(d.y));
}

void Graph::update(sf::Vector2<number> d, unsigned int intervals, number (*func)(number))
{
    m_domain = d;
    number dif = std::abs((d.y - d.x) / intervals);
    int i = 0;
    for (number x = d.x; x < d.y - dif / 10; x += dif) {
        number y = func(x);
        m_range = {std::min(m_range.x, y), std::max(m_range.y, y)};
        m_graph.at(i) = {x, y};
        i++;
    }
    m_graph.emplace_back(d.y, func(d.y));
}

void Graph::print()
{
    std::cout << "x: ";
    for (sf::Vector2<number> p : m_graph)
    {
        std::string str = std::to_string(p.x);
        std::cout << str;

        // Calculate and print the spaces between each x
        int r_padding = 1;
        int lx = str.length();
        int ly = std::to_string(p.y).length();
        // Calculate difference between the lengths of x and y
        if (ly > lx) {
            r_padding += ly - lx;
        }
        std::cout << std::string(r_padding, ' ');
    }

    std::cout << "\ny: ";
    for (sf::Vector2<number> p : m_graph)
    {
        std::string str = std::to_string(p.y);
        std::cout << str;

        int r_padding = 1;
        int lx = std::to_string(p.x).length();
        int ly = str.length();
        if (lx > ly) {
            r_padding += lx - ly;
        }
        std::cout << std::string(r_padding, ' ');
    }
}

const std::vector<sf::Vector2<number>>& Graph::get_data()
{
    return m_graph;
}

sf::Vector2<number> Graph::get_domain()
{
    return m_domain;
}

sf::Vector2<number> Graph::get_range()
{
    return m_range;
}

} // namespace math