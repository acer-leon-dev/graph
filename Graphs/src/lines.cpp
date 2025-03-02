#include <cmath>
#include <algorithm>

#include "lines.hpp"

namespace
{
    
float _ipart(int x)
{
    return std::floor(x);
}

float _round(int x)
{
    return _ipart(x + 0.5);
}

float _fpart(int x)
{
    return x - _ipart(x);
}

float _rfpart(int x)
{
    return 1 - _fpart(x);
}

sf::Color _adjust_opacity(const sf::Color& c, float opacity)
{
    auto newc = c;
    newc.a * opacity;
    return newc;
}

void _draw_pixel(sf::RenderWindow& window, sf::Vertex p)
{
    sf::RectangleShape pixel{{1, 1}};
    pixel.setFillColor(p.color);
    pixel.setPosition(p.position);
    window.draw(pixel);
}

void _draw_line_AA(sf::RenderWindow& window, sf::Vector2f p1, sf::Vector2f p2, sf::Color c, int thickness)
{
    float x0 = p1.x;
    float x1 = p2.x;
    float y0 = p1.y;
    float y1 = p2.y;
    
    bool steep = std::abs(y1 - y0) > abs(x1 - x0);

    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    } 
    
    if (x0 > x1) 
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    
    float dx = x1 - x0;
    float dy = y1 - y0;

    float gradient;
    if (dx == 0.0) {
        gradient = 1.0;
    }
    else
    {
        gradient = dy / dx;
    }

    // handle first endpoint
    float xend = round(x0);
    float yend = y0 + gradient * (xend - x0);
    float xgap = _rfpart(x0 + 0.5);
    float xpxl1 = xend; // this will be used in the main loop
    float ypxl1 = _ipart(yend);
    
    if (steep)
    {
        _draw_pixel(window, {{ypxl1, xpxl1}, _adjust_opacity(c, _rfpart(yend) * xgap)});
        _draw_pixel(window, {{ypxl1+1, xpxl1}, _adjust_opacity(c, _fpart(yend) * xgap)});
    }
    else 
    {
        _draw_pixel(window, {{xpxl1, ypxl1}, _adjust_opacity(c, _rfpart(yend) * xgap)});
        _draw_pixel(window, {{xpxl1, ypxl1 + 1}, _adjust_opacity(c, _fpart(yend) * xgap)});
    }

    float intery = yend + gradient; // first y-intersection for the main loop
    
    // handle second endpoint
    xend = round(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = _fpart(x1 + 0.5);
    float xpxl2 = xend; //this will be used in the main loop
    float ypxl2 = _ipart(yend);

    if (steep)
    {
        _draw_pixel(window, {{ypxl2, xpxl2}, _adjust_opacity(c, _rfpart(yend) * xgap)});
        _draw_pixel(window, {{ypxl2 + 1, xpxl2}, _adjust_opacity(c, _fpart(yend) * xgap)});
    }
    else
    {
        _draw_pixel(window, {{xpxl2, ypxl2}, _adjust_opacity(c, _rfpart(yend) * xgap)});
        _draw_pixel(window, {{xpxl2, ypxl2 + 1}, _adjust_opacity(c, _fpart(yend) * xgap)});
    }
    
    // main loop
    if (steep)
    {
        for (float x = xpxl1 + 1; x <= xpxl2 - 1; x++)
        {
            _draw_pixel(window, {{_ipart(intery), x}, _adjust_opacity(c, _fpart(intery))});
            _draw_pixel(window, {{_ipart(intery) + 1, x}, _adjust_opacity(c, _fpart(intery))});
            intery += gradient;
        }
    }
    else
    {
        for (float x = xpxl1 + 1; x <= xpxl2 - 1; x++)
        {
            _draw_pixel(window, {{x, _ipart(intery)},  _adjust_opacity(c, _fpart(intery))});
            _draw_pixel(window, {{x, _ipart(intery) + 1}, _adjust_opacity(c, _fpart(intery))});
            intery += gradient;
        }
    }
}

void _draw_square(sf::RenderWindow& window, sf::Vector2f pos, sf::Color c, float length)
{
    sf::RectangleShape square{{length, length}};
    square.setFillColor(c);
    square.setPosition(pos);
    window.draw(square);
}

void _draw_line_noAA(sf::RenderWindow &window, sf::Vector2f p1, sf::Vector2f p2, sf::Color c, int thickness)
{
    int x0 = p1.x;
    int y0 = p1.y;
    int x1 = p2.x;
    int y1 = p2.y;
    int dx = abs(x1 - x0);
    int sx, sy;
    if (x0 < x1)
    {
        sx = 1;
    }
    else
    {
        sx = -1;
    }

    int dy = -abs(y1 - y0);
    if (y0 < y1)
    {
        sy = 1;
    }
    else
    {
        sy = -1;
    }

    int err = dx + dy;

    while (true)
    {
        _draw_square(window, {static_cast<float>(x0), static_cast<float>(y0)}, c, thickness);

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

}

void drawLine(sf::RenderWindow &window, sf::Vector2f point1, sf::Vector2f point2, sf::Color color, int thickness, bool antialiased)
{
    if (antialiased)
    {
        _draw_line_AA(window, point1, point2, color, thickness);
    }
    else
    {
        _draw_line_noAA(window, point1, point2, color, thickness);
    }

}

void drawLines(sf::RenderWindow &window, const std::vector<sf::Vector2f>& points)
{
    int right = 1;
    for (int left = 0; left < points.size() - 1; left++) {
        // if (std::isnan(points[right].y)) {
        //     right++;
        //     continue;
        // }

        drawLine(window, points[left], points[right], sf::Color(0x4452f2), 3, true);
        right++;
    }
}