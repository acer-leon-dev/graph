#pragma once

#include "pch.hpp"

////////////////////////////////////////////////////////////
/// \brief Generator for Bersenham's Line Drawing Algorithm
////////////////////////////////////////////////////////////
class Bresenham
{
public:
    Bresenham(const sf::Vector2i& p1, const sf::Vector2i& p2);

    sf::Vector2i operator() () const;
    sf::Vector2i operator*() const;
    bool atEnd() const;
    bool next();
    bool prev();
    Bresenham& operator ++ ();
    Bresenham operator ++ (int);
    Bresenham& operator -- ();
    Bresenham operator -- (int);

private:
    void m_advance_next();
    void m_advance_prev();
    bool m_at_end() const;
    bool m_not_at_end() const;

    int m_x0;
    int m_y0;
    int m_x1;
    int m_y1;

    int m_differencex;
    int m_differencey;

    int m_sx;
    int m_sy;

    int m_error;
};
