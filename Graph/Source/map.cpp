namespace {
    // For returning multiple numbers
    struct domain {
        double lo;
        double hi;
    };
}

// Multiply domain by scale
domain operator*(const domain& l_dom, const double& r) {
    return {l_dom.lo * r, l_dom.hi * r};
}

// Multiply domain scale
domain operator*(const domain& l_dom, const domain& r_dom) {
    return {l_dom.lo * l_dom.lo, l_dom.hi * r_dom.hi};
}

// Divide domain by scale
domain operator/(const domain& l_dom, const double& r) {
    return {l_dom.lo / r, l_dom.hi / r};
}

// Divide domain scale
domain operator/(const domain& l_dom, const domain& r_dom) {
    return {l_dom.lo / l_dom.lo, l_dom.hi / r_dom.hi};
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