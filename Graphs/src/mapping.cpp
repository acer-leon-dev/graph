#include "mapping.hpp"

namespace mapping {

// Multiply domain by scale
domain operator*(const domain& l_dom, const double& r) {
    return {l_dom.first * r, l_dom.second * r};
}

// Multiply domain scale
domain operator*(const domain& l_dom, const domain& r_dom) {
    return {l_dom.first * r_dom.first, l_dom.second * r_dom.second};
}

// Divide domain by scale
domain operator/(const domain& l_dom, const double& r) {
    return {l_dom.first / r, l_dom.second / r};
}

// Divide domain scale
domain operator/(const domain& l_dom, const domain& r_dom) {
    return {l_dom.first / r_dom.first, l_dom.second / r_dom.second};
}

// {0, 1}
// Converts a value to it's normalized equivalent
double map_to_normal(double value, double min, double max) {
    return value / (max - min);
}

// {0, 1}, {0, 1}
// Converts a domain/coordinate to it's normalized equivalent
domain map_to_normal(double x, double min_x, double max_x,double y, double min_y, double max_y) {
    return {map_to_normal(x, min_x, max_x), map_to_normal(y, min_y, max_y)};
}

// Converts a normalized value to some scale
double map_to_raster(double value, double scale) {
    return value * scale;
}

// Converts a normalized domain/coordinate to a given scale
domain map_to_raster(double x, double scale_x, double y, double scale_y) {
    return {map_to_raster(x, scale_x), map_to_raster(y, scale_y)};
}

domain map_to_raster(domain dom, double scale_x, double scale_y) {
    return dom * domain{scale_x, scale_y};
}
} // namespace mapping