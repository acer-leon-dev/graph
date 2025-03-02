#pragma once

#include "SFML/System.hpp"

namespace mapping {

// {0, 1}
// Converts a value to it's normalized equivalent
float map_to_normal(float value, float min, float max);

// {0, 1}, {0, 1}
// Converts a domain/coordinate to it's normalized equivalent
sf::Vector2f map_to_normal(float x, float min_x, float max_x,float y, float min_y, float max_y);

// Converts a normalized value to some scale
float map_to_raster(float value, float scale);

// Converts a normalized domain/coordinate to a given scale
sf::Vector2f map_to_raster(float x, float scale_x, float y, float scale_y);

sf::Vector2f map_to_raster(sf::Vector2f dom, float scale_x, float scale_y);

} // namespace mapping