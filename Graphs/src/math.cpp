#include "math.hpp"

namespace math {

Graph::Graph(sf::Vector2<double> domain, std::function<double(double)> func, unsigned int intervals)
:   m_domain{domain},
    m_range{-10, 10},
    m_func{func}
{
    m_graph.reserve(intervals);
    
    m_range.x = m_func(m_domain.x);
    m_range.y = m_func(m_domain.y);

    double dx = std::abs((m_domain.y - m_domain.x) / intervals);
    for (double i_x = m_domain.x; i_x < m_domain.y; i_x += dx)
    {
        double y = m_func(i_x);
        m_range.x = std::min(m_range.x, y);
        m_range.y = std::max(m_range.y, y);
        m_graph.emplace_back(i_x, y);
    }
    
    m_graph.emplace_back(m_domain.y, m_func(m_domain.y));
}

void Graph::update(sf::Vector2<double> domain, std::function<double(double)> func, unsigned int intervals)
{
    m_domain = domain;
    m_func = func;

    m_range.x = m_func(m_domain.x);
    m_range.y = m_func(m_domain.y);

    double dx = std::abs((domain.y - domain.x) / intervals);
    int i = 0;
    for (double x = domain.x; x < domain.y; x += dx) {
        double y = func(x);
        m_range.x = std::min(m_range.x, y);
        m_range.y = std::max(m_range.y, y);
        m_graph.at(i) = {x, y};
        i++;
    }

    m_graph.back() = {domain.y, func(domain.y)};
}

const std::vector<sf::Vector2<double>>& Graph::getData()
{
    return m_graph;
}

sf::Vector2<double> Graph::getDomain()
{
    return m_domain;
}

sf::Vector2<double> Graph::getRange()
{
    return m_range;
}

std::function<double(double)> Graph::getFunction()
{
    return m_func;
}


} // namespace math