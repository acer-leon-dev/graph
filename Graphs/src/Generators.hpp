#pragma once

#include "pch.hpp"

class Bresenham
{
public:
    Bresenham(sf::Vector2i, sf::Vector2i);

    sf::Vector2i operator() () const;
    sf::Vector2i operator*() const;
    bool atEnd() const;
    Bresenham& next();
    Bresenham& prev();
    Bresenham& operator ++ ();
    Bresenham operator ++ (int);
    Bresenham& operator -- ();
    Bresenham operator -- (int);

private:
    void m_next();
    void m_prev();

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
