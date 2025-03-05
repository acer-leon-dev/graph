#include "Generators.hpp"
#include <stdexcept>

Bresenham::Bresenham(const sf::Vector2i& p1, const sf::Vector2i& p2)
:   m_x0{p1.x},
    m_y0{p1.y},
    m_x1{p2.x},
    m_y1{p2.y},
    m_sx{m_x0 < m_x1 ? 1 : -1},
    m_sy{m_y0 < m_y1 ? 1 : -1},
    m_differencex{std::abs(m_x1 - m_x0)},
    m_differencey{-std::abs(m_y1 - m_y0)},
    m_error {m_differencex + m_differencey}
{
    
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
    return m_at_end();
}

// Move to next value
bool Bresenham::next()
{
    m_advance_next();
    return m_not_at_end();
}

// Move to previous value
bool Bresenham::prev()
{
    m_advance_prev();
    return m_not_at_end();
}

// pre-increment (++obj)
Bresenham& Bresenham::operator++()
{
    next();
    return *this;
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
    prev();
    return *this;
}

// pre-decrement (obj++)
Bresenham Bresenham::operator--(int)
{
    Bresenham old = *this;
    this->operator--();
    return old;
}

void Bresenham::m_advance_next()
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

void Bresenham::m_advance_prev()
{
    int error2 = 2 * m_error;

    if (error2 > m_differencex)
    {
        m_y0 -= m_sy;
        m_error -= m_differencex;
    }

    if (error2 < m_differencey)
    {
        m_x0 -= m_sx;
        m_error -= m_differencey;
    }
}

bool Bresenham::m_not_at_end() const
{
    // return m_sx * m_x0 <= m_x1 * m_sx || m_sy * m_y0 <= m_y1 * m_sy;
    return m_x0 != m_x1 || m_y0 != m_y1;
}

bool Bresenham::m_at_end() const
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
    //
    // if (m_sy == 1 && m_y0 <= m_y1)
    // {
    //     return false;
    // }
    // else if (m_y0 >= m_y1)
    // {
    //     return false;
    // }

    //// Method 3
    return m_x0 == m_x1 && m_y0 == m_y1;

    //// Method 2 : opposite process as Method 1
    // return m_sx * m_x0 > m_x1 * m_sx && m_sy * m_y0 > m_y1 * m_sy;
}