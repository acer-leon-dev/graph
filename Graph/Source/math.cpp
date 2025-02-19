#include "Graph/math.hpp"
#include <string>
#include <iostream>
#include <algorithm>

void point::print() {
    std::cout << "(" << x << ", " << y << ")";
}

void domain::print() {
    std::cout << "{" << low << ", " << high << "}";
}

void range::print() {
    std::cout << "{" << low << ", " << high << "}";
}

Graph::Graph(domain d, unsigned int intervals, number (*func)(number)) {
    m_domain = d;
    number dif = std::abs((d.high - d.low) / intervals);
    m_graph.reserve(intervals);
    for (number x = d.low; x < d.high - dif / 10; x += dif) {
        number y = func(x);
        m_range.low = std::min(m_range.low, y);
        m_range.high = std::max(m_range.high, y);
        m_graph.emplace_back(x, func(x));
    }
    m_graph.emplace_back(d.high, func(d.high));
}

void Graph::print() {
    std::cout << "x: ";
    for (point p : m_graph)
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
    for (point p : m_graph)
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

const std::vector<point>& Graph::get_data() {
    return m_graph;
}

domain Graph::get_domain() {
    return m_domain;
}

range Graph::get_range() {
    return m_range;
}