#include "Lines.hpp"
#include <algorithm>
#include <cmath>

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

void _swap(float& x, float& y)
{
    float temp = x;
    x = y;
    y = temp;
}

sf::Color _adjust_color_opacity(const sf::Color& c, float opacity)
{
    auto newc = c;
    newc.a * opacity;
    return newc;
}

void _draw_pixel(sf::RenderTarget& target, sf::Vertex p)
{
    sf::RectangleShape pixel{{1, 1}};
    pixel.setFillColor(p.color);
    pixel.setPosition(p.position);
    target.draw(pixel);
}

void _draw_line_AA(sf::RenderTarget& target, sf::Vector2f p1, sf::Vector2f p2, sf::Color c)
{
    // Xaolin Wu's Line Drawing Algorithm

    float x0 = p1.x;
    float x1 = p2.x;
    float y0 = p1.y;
    float y1 = p2.y;
    
    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

    if (steep)
    {
        _swap(x0, y0);
        _swap(x1, y1);
    } 
    
    if (x0 > x1) 
    {
        _swap(x0, x1);
        _swap(y0, y1);
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
    float xend = _round(x0);
    float yend = y0 + gradient * (xend - x0);
    float xgap = _rfpart(x0 + 0.5);
    float xpxl1 = xend; // this will be used in the main loop
    float ypxl1 = _ipart(yend);
    
    if (steep)
    {
        _draw_pixel(target, {{ypxl1, xpxl1}, _adjust_color_opacity(c, _rfpart(yend) * xgap)});
        _draw_pixel(target, {{ypxl1+1, xpxl1}, _adjust_color_opacity(c, _fpart(yend) * xgap)});
    }
    else 
    {
        _draw_pixel(target, {{xpxl1, ypxl1}, _adjust_color_opacity(c, _rfpart(yend) * xgap)});
        _draw_pixel(target, {{xpxl1, ypxl1 + 1}, _adjust_color_opacity(c, _fpart(yend) * xgap)});
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
        _draw_pixel(target, {{ypxl2, xpxl2}, _adjust_color_opacity(c, _rfpart(yend) * xgap)});
        _draw_pixel(target, {{ypxl2 + 1, xpxl2}, _adjust_color_opacity(c, _fpart(yend) * xgap)});
    }
    else
    {
        _draw_pixel(target, {{xpxl2, ypxl2}, _adjust_color_opacity(c, _rfpart(yend) * xgap)});
        _draw_pixel(target, {{xpxl2, ypxl2 + 1}, _adjust_color_opacity(c, _fpart(yend) * xgap)});
    }
    
    // main loop
    if (steep)
    {
        for (float x = xpxl1 + 1; x <= xpxl2 - 1; x++)
        {
            _draw_pixel(target, {{_ipart(intery), x}, _adjust_color_opacity(c, _fpart(intery))});
            _draw_pixel(target, {{_ipart(intery) + 1, x}, _adjust_color_opacity(c, _fpart(intery))});
            intery += gradient;
        }
    }
    else
    {
        for (float x = xpxl1 + 1; x <= xpxl2 - 1; x++)
        {
            _draw_pixel(target, {{x, _ipart(intery)},  _adjust_color_opacity(c, _fpart(intery))});
            _draw_pixel(target, {{x, _ipart(intery) + 1}, _adjust_color_opacity(c, _fpart(intery))});
            intery += gradient;
        }
    }
}

void _draw_square(sf::RenderTarget& target, sf::Vector2f pos, sf::Color c, float length)
{
    sf::RectangleShape square{{length, length}};
    square.setFillColor(c);
    square.setPosition(pos);
    target.draw(square);
}

void _draw_line_noAA(sf::RenderTarget& target, sf::Vector2f p1, sf::Vector2f p2, sf::Color c, int weight)
{
    // Bersenham's Line Drawing Algorithm

    int x0 = p1.x;
    int y0 = p1.y;
    int x1 = p2.x;
    int y1 = p2.y;
    int dx = std::abs(x1 - x0);
    int sx, sy;

    if (x0 < x1)
    {
        sx = 1;
    }
    else
    {
        sx = -1;
    }

    if (y0 < y1)
    {
        sy = 1;
    }
    else
    {
        sy = -1;
    }

    int dy = -std::abs(y1 - y0);
    int err = dx + dy;

    while (true)
    {
        _draw_square(target, {static_cast<float>(x0), static_cast<float>(y0)}, c, weight);

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


void _write_rectangle(std::vector<uint8_t>& pixels, sf::IntRect rect, sf::Color c)
{
    for (int y = rect.position.y; y < rect.position.y + rect.size.y; y++)
    {
        for (int x = rect.position.x; x < rect.position.x + rect.size.y; x++)
        {
            pixels[y * rect.size.x + x] =     c.r;
            pixels[y * rect.size.x + x + 1] = c.g;
            pixels[y * rect.size.x + x + 2] = c.b;
            pixels[y * rect.size.x + x + 3] = c.a;
        }
    }
}

void _write_line_noaa_to_array(std::vector<uint8_t>& pixels, sf::Vector2i p1, sf::Vector2i p2, sf::Color c, int weight)
{
    // Bersenham's Line Drawing Algorithm

    int x0 = p1.x;
    int y0 = p1.y;
    int x1 = p2.x;
    int y1 = p2.y;
    int dx = std::abs(x1 - x0);
    int sx, sy;

    if (x0 < x1)
    {
        sx = 1;
    }
    else
    {
        sx = -1;
    }

    if (y0 < y1)
    {
        sy = 1;
    }
    else
    {
        sy = -1;
    }

    int dy = -std::abs(y1 - y0);
    int err = dx + dy;

    while (true)
    {
        _write_rectangle(pixels, {{x0, y0}, {weight, weight}}, c);

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

void _write_lines_noaa_to_array(std::vector<uint8_t>& pixels, sf::Color color, int weight, const std::vector<sf::Vector2i>& points)
{
    unsigned int right = 1;
    for (unsigned int left = 0; left < points.size() - 1; left++) {
        _write_line_noaa_to_array(pixels, points[left], points[right], color, weight);
        right++;
    }
}

} // [anonymous] namespace

////////////////////////////////////////////////////////////////////////////////

void drawLine(sf::RenderTarget &target, sf::Vector2f point1, sf::Vector2f point2, sf::Color color, int weight, bool antialiased)
{
    if (antialiased)
    {
        _draw_line_AA(target, point1, point2, color);
    }
    else
    {
        _draw_line_noAA(target, point1, point2, color, weight);
    }

}

////////////////////////////////////////////////////////////////////////////////

void drawLines(sf::RenderTarget &target, sf::Color color, int weight, bool antialiased, const std::vector<sf::Vector2f>& points)
{
    for (unsigned int left = 0; left < points.size() - 1; left++) {
        drawLine(target, points[left], points[left + 1], color, weight, antialiased);
    }
}

//////////////////////////////////////// class LinesLegacy ////////////////////////////////////////

LinesLegacy::LinesLegacy() 
:   m_points(), 
    m_color(sf::Color::Black), 
    m_weight(1), 
    m_antialiased(true)
{

}

LinesLegacy::LinesLegacy(const std::vector<sf::Vector2f>& points) 
:   m_points(points), 
    m_color(sf::Color::Black), 
    m_weight(1), 
    m_antialiased(true)
{
    
}

void LinesLegacy::setPoints(const std::vector<sf::Vector2f>& points)
{
    m_points = points;
}

const std::vector<sf::Vector2f>& LinesLegacy::getPoints() const
{
    return m_points;
}

void LinesLegacy::setColor(sf::Color color)
{
    m_color = color;
}

sf::Color LinesLegacy::getColor() const
{
    return m_color;
}

void LinesLegacy::setWeight(int weight)
{
    m_weight = weight;
}

int LinesLegacy::getWeight() const
{
    return m_weight;
}

void LinesLegacy::setAntialiased(bool antialiased)
{
    m_antialiased = antialiased;
}

bool LinesLegacy::getAntialiased() const
{
    return m_antialiased;
}

void LinesLegacy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    drawLines(target, m_color, m_weight, m_antialiased, m_points);
}

//////////////////////////////////////// class Lines ////////////////////////////////////////

Lines::Lines(sf::Vector2i domain, sf::Vector2i range) 
:   m_points{}, 
    m_color{sf::Color::Black}, 
    m_weight{1}, 
    // m_antialiased{false},
    m_width{std::abs(domain.y - domain.x)},
    m_height{std::abs(range.y - range.x)},
    m_pixels(m_width * m_height * 4, 0),
    m_texture{{m_width, m_height}},
    m_sprite{m_texture}
{
    
}

Lines::Lines(const std::vector<sf::Vector2i>& points, sf::Vector2i domain, sf::Vector2i range) 
:   m_points{points},
    m_color{sf::Color::Black}, 
    m_weight{1}, 
    // m_antialiased{false},
    m_width{std::abs(domain.y - domain.x)},
    m_height{std::abs(range.y - range.x)},
    m_pixels(m_width * m_height * 4, 0),
    m_texture{{m_width, m_height}},
    m_sprite{m_texture}
{
    _write_lines_noaa_to_array(m_pixels, m_color, m_weight, m_points);
}

void Lines::update()
{
    _write_lines_noaa_to_array(m_pixels, m_color, m_weight, m_points);
}

void Lines::setPoints(const std::vector<sf::Vector2i>& points)
{
    m_points = points;
}

const std::vector<sf::Vector2i>& Lines::getPoints() const
{
    return m_points;
}

void Lines::setColor(sf::Color color)
{
    m_color = color;
}

sf::Color Lines::getColor() const
{
    return m_color;
}

void Lines::setWeight(int weight)
{
    m_weight = weight;
}

int Lines::getWeight() const
{
    return m_weight;
}

// void Lines::setAntialiased(bool antialiased)
// {
//     m_antialiased = antialiased;
// }

// bool Lines::getAntialiased() const
// {
//     return m_antialiased;
// }

void Lines::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}