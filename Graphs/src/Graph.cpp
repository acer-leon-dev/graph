#include "Graph.hpp"

namespace
{
    sf::Vector2<double> _sortInterval(sf::Vector2<double> value)
    {
        if (value.y < value.x)
        {
            std::swap(value.x, value.y);
        }

        return value;
    }
}

Graph::Graph()
:   m_domain{-10, 10},
    m_range{-10, 10},
    m_func{[](double x){ return 0; }}
{

}

Graph::Graph(sf::Vector2<double> domain, std::function<double(double)> func, unsigned int subints)
:   m_domain{_sortInterval(domain)},
    m_range{-10, 10},
    m_func{func}
{
    m_points.reserve(subints + 1);

    m_range.x = m_func(m_domain.x);
    m_range.y = m_func(m_domain.y);
    
    if (subints != 0)
    {  
        double dx = std::abs((m_domain.y - m_domain.x) / subints);
        
        for (double x = m_domain.x; x <= m_domain.y; x += dx)
        {
            double y = m_func(x);
            m_range.x = std::min(m_range.x, y);
            m_range.y = std::max(m_range.y, y);
            m_points.emplace_back(x, y);
        }
    }
    m_points.emplace_back(m_domain.y, m_func(m_domain.y));
    m_range = _sortInterval(m_range);
}

void Graph::update(sf::Vector2<double> domain, std::function<double(double)> func, unsigned int subints)
{
    m_points.resize(subints + 1);

    m_domain = _sortInterval(domain);
    m_func = func;
    
    m_range.x = m_func(m_domain.x);
    m_range.y = m_func(m_domain.y);

    if (subints != 0)
    {
        double dx = std::abs((domain.y - domain.x) / subints);
        
        // for (int i = 0; i < m_points.size(); i++)
        // {
        //     double x = i * dx;
        //     double y = func(x);
        //     m_range.x = std::min(m_range.x, y);
        //     m_range.y = std::max(m_range.y, y);
        //     m_points.at(i) = {x, y};
        // }

        int i = -1;
        for (double x = domain.x; x < domain.y; x += dx) {
            i++;
            double y = func(x);
            m_range.x = std::min(m_range.x, y);
            m_range.y = std::max(m_range.y, y);
            m_points.at(i) = {x, y};
        }
    }

    m_points.back() = {domain.y, func(domain.y)};
    m_range = _sortInterval(m_range);
}

const std::vector<sf::Vector2<double>> Graph::getPoints() const
{
    return m_points;
}

sf::Vector2<double> Graph::getDomain() const
{
    return m_domain;
}

sf::Vector2<double> Graph::getRange() const
{
    return m_range;
}

std::function<double(double)> Graph::getFunction() const
{
    return m_func;
}

double Graph::getWidth() const
{
    return std::abs(m_domain.y - m_domain.x);
}

double Graph::getHeight() const
{
    return std::abs(m_range.y - m_range.x);
}

int Graph::getSubintervals() const
{
    return m_points.size() - 1;
}