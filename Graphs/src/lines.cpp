#include "Lines.hpp"
#include "Generators.hpp"

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

void _drawPixelToTarget(sf::RenderTarget& target, sf::Vertex p)
{
    sf::RectangleShape pixel{{1, 1}};
    pixel.setFillColor(p.color);
    pixel.setPosition(p.position);
    target.draw(pixel);
}

void _drawLineAAONToTarget(sf::RenderTarget& target, sf::Vector2f p1, sf::Vector2f p2, sf::Color c)
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
    else {
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
        _drawPixelToTarget(target, {{ypxl1, xpxl1}, _adjust_color_opacity(c, _rfpart(yend) * xgap)});
        _drawPixelToTarget(target, {{ypxl1+1, xpxl1}, _adjust_color_opacity(c, _fpart(yend) * xgap)});
    }
    else 
    {
        _drawPixelToTarget(target, {{xpxl1, ypxl1}, _adjust_color_opacity(c, _rfpart(yend) * xgap)});
        _drawPixelToTarget(target, {{xpxl1, ypxl1 + 1}, _adjust_color_opacity(c, _fpart(yend) * xgap)});
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
        _drawPixelToTarget(target, {{ypxl2, xpxl2}, _adjust_color_opacity(c, _rfpart(yend) * xgap)});
        _drawPixelToTarget(target, {{ypxl2 + 1, xpxl2}, _adjust_color_opacity(c, _fpart(yend) * xgap)});
    }
    else
    {
        _drawPixelToTarget(target, {{xpxl2, ypxl2}, _adjust_color_opacity(c, _rfpart(yend) * xgap)});
        _drawPixelToTarget(target, {{xpxl2, ypxl2 + 1}, _adjust_color_opacity(c, _fpart(yend) * xgap)});
    }
    
    // main loop
    if (steep)
    {
        for (float x = xpxl1 + 1; x <= xpxl2 - 1; x++)
        {
            _drawPixelToTarget(target, {{_ipart(intery), x}, _adjust_color_opacity(c, _fpart(intery))});
            _drawPixelToTarget(target, {{_ipart(intery) + 1, x}, _adjust_color_opacity(c, _fpart(intery))});
            intery += gradient;
        }
    }
    else
    {
        for (float x = xpxl1 + 1; x <= xpxl2 - 1; x++)
        {
            _drawPixelToTarget(target, {{x, _ipart(intery)},  _adjust_color_opacity(c, _fpart(intery))});
            _drawPixelToTarget(target, {{x, _ipart(intery) + 1}, _adjust_color_opacity(c, _fpart(intery))});
            intery += gradient;
        }
    }
}

void _drawSquareToTarget(sf::RenderTarget& target, sf::Vector2f pos, sf::Color c, float length)
{
    sf::RectangleShape square{{length, length}};
    square.setFillColor(c);
    square.setPosition(pos);
    target.draw(square);
}

void _drawLineAAOFFToTarget(sf::RenderTarget& target, sf::Vector2f p1, sf::Vector2f p2, sf::Color c, int weight)
{
    // Bersenham's Line Drawing Algorithm
    Bresenham gen{static_cast<sf::Vector2i>(p1), static_cast<sf::Vector2i>(p2)};
    do {
        sf::Vector2f point = static_cast<sf::Vector2f>(gen());
        _drawSquareToTarget(target, point, c, weight);
    } while (gen.next());
}

uint8_t& _accessPixelArrayPart(uint8_t* pixelarray, sf::Vector2u pixelarraysize, int x, int y, int part)
{
    return pixelarray[part + 4 * (x + pixelarraysize.x * y)];
    // return pixelarray[y * pixelarraywidth * 4 + x];
}

void _writeRectangleToArray(uint8_t* pixelarray, sf::IntRect rect, sf::Color c)
{
    for (int y = rect.position.y; y < rect.position.y + rect.size.y; y++)
    {
        for (int x = rect.position.x; x < rect.position.x + rect.size.y; x++)
        {
            _accessPixelArrayPart(pixelarray, static_cast<sf::Vector2u>(rect.size), x, y, 0) = c.r;
            _accessPixelArrayPart(pixelarray, static_cast<sf::Vector2u>(rect.size), x, y, 1) = c.g;
            _accessPixelArrayPart(pixelarray, static_cast<sf::Vector2u>(rect.size), x, y, 2) = c.b;
            _accessPixelArrayPart(pixelarray, static_cast<sf::Vector2u>(rect.size), x, y, 3) = c.a;
        }
    }
}

void _writeLineAAOFFToArray(uint8_t* pixelarray, sf::Vector2u p1, sf::Vector2u p2, sf::Color c, int weight)
{
    // Bersenham's Line Drawing Algorithm
    Bresenham gen{static_cast<sf::Vector2i>(p1), static_cast<sf::Vector2i>(p2)};
    do {
        sf::Vector2u point = static_cast<sf::Vector2u>(gen());
        point.y *= -1;
        sf::IntRect rect{static_cast<sf::Vector2i>(point), {weight, weight}};
        _writeRectangleToArray(pixelarray, rect, c);
    } while (gen.next());
}

void _writeLinesAAOFFToArray(uint8_t* pixelarray, const std::vector<sf::Vector2u>& points, sf::Color color, int weight)
{
    for (unsigned int left = 0; left < points.size() - 1; left++) {
        _writeLineAAOFFToArray(pixelarray, points[left], points[left + 1], color, weight);
    }
}

} // [anonymous] namespace

////////////////////////////////////////////////////////////////////////////////

void drawLine(sf::RenderTarget &target, sf::Vector2f point1, sf::Vector2f point2, sf::Color color, int weight, bool antialiased)
{
    if (antialiased) {
        _drawLineAAONToTarget(target, point1, point2, color);
    }
    else {
        _drawLineAAOFFToTarget(target, point1, point2, color, weight);
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

Lines::Lines(sf::Texture& texture, const std::vector<sf::Vector2u>& points) 
:   m_texture{texture},
    m_points{points}, 
    m_color{sf::Color::Black}, 
    m_weight{1}, 
    m_width{m_texture.getSize().x},
    m_height{m_texture.getSize().y},
    // m_antialiased{false},
    m_pixels(m_width * m_height * 4, 0)
{
}


sf::Texture& Lines::getTexture()
{
    return m_texture;
}

void Lines::updateTexture()
{
    uint8_t* ptr_pixelarray = m_pixels.data();
    _writeLinesAAOFFToArray(ptr_pixelarray, m_points, m_color, m_weight);
    m_texture.update(ptr_pixelarray);
}

void Lines::setPoints(const std::vector<sf::Vector2u>& points)
{
    m_points = points;
}

const std::vector<sf::Vector2u>& Lines::getPoints() const
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

// void Lines::draw(sf::RenderTarget& target, sf::RenderStates states) const
// {
//     target.draw(m_sprite);
// }