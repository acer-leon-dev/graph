#include "Generators.hpp"
#include <stdexcept>

Bresenham::Bresenham(sf::Vector2i p1, sf::Vector2i p2)
{
    m_x0 = p1.x;
    m_y0 = p1.y;
    m_x1 = p2.x;
    m_y1 = p2.y;

    m_differencex = std::abs(m_x1 - m_x0);
    m_differencey = -std::abs(m_y1 - m_y0);

    if (m_x0 < m_x1)
    {
        m_sx = 1;
    }
    else
    {
        m_sx = -1;
    }

    if (m_y0 < m_y1)
    {
        m_sy = 1;
    }
    else
    {
        m_sy = -1;
    }

    m_error = m_differencex + m_differencey;
}

// return current value
sf::Vector2i Bresenham::operator()() const
{
    return {m_x0, m_y0};
}

// return current value
sf::Vector2i Bresenham::operator*() const
{
    return this->operator()();
}

// Return true if at end
bool Bresenham::atEnd() const
{
    //// Method 1

    // if (m_sx == 1 && m_x0 <= m_x1)
    // {
    //     return false;
    // }
    // else if (m_x0 >= m_x1)
    // {
    //     return false;
    // }
    
    // if (m_sy == 1 && m_y0 <= m_y1)
    // {
    //     return false;
    // }
    // else if (m_y0 >= m_y1)
    // {
    //     return false;
    // }

    //// Method 2 : same process and Method 1
    
    if (m_sx * m_x0 <= m_x1 * m_sx || m_sy * m_y0 <= m_y1 * m_sy)
    {
        return false;
    }
    
    return true;

    //// Method 3

    // return m_x0 == m_x1 && m_y0 == m_y1;
}

// Move to next value
Bresenham& Bresenham::next()
{
    m_next();
    return *this;
}

// Move to previous value
Bresenham& Bresenham::prev()
{
    m_prev();
    return *this;
}

// pre-increment (++obj)
Bresenham& Bresenham::operator++()
{
    return this->next();
}

// post-increment (obj++)
Bresenham Bresenham::operator++(int)
{
    Bresenham old = *this;
    this->operator++();
    return old;
}

// pre-decrement (++obj)
Bresenham& Bresenham::operator--()
{
    return this->prev();
}

// pre-decrement (obj++)
Bresenham Bresenham::operator--(int)
{
    Bresenham old = *this;
    this->operator--();
    return old;
}

void Bresenham::m_next()
{
    int error2 = 2 * m_error;

    if (error2 >= m_differencey)
    {
        m_error += m_differencey;
        m_x0 += m_sx;
    }

    if (error2 <= m_differencex)
    {
        m_error += m_differencex;
        m_y0 += m_sy;
    }
}

void Bresenham::m_prev()
{
    
}