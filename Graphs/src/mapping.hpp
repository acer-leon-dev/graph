#ifndef A4F2D5F6_5370_484D_A727_F15C776309C6
#define A4F2D5F6_5370_484D_A727_F15C776309C6

namespace mapping {

// For returning multiple numbers
struct domain {
    double first;
    double second;
};

// Multiply domain by scale
domain operator*(const domain& l_dom, const double& r);

// Multiply domain scale
domain operator*(const domain& l_dom, const domain& r_dom);

// Divide domain by scale
domain operator/(const domain& l_dom, const double& r);

// Divide domain scale
domain operator/(const domain& l_dom, const domain& r_dom);

// {0, 1}
// Converts a value to it's normalized equivalent
double map_to_normal(double value, double min, double max);

// {0, 1}, {0, 1}
// Converts a domain/coordinate to it's normalized equivalent
domain map_to_normal(double x, double min_x, double max_x,double y, double min_y, double max_y);

// Converts a normalized value to some scale
double map_to_raster(double value, double scale);

// Converts a normalized domain/coordinate to a given scale
domain map_to_raster(double x, double scale_x, double y, double scale_y);

domain map_to_raster(domain dom, double scale_x, double scale_y);

} // namespace mapping


#endif /* A4F2D5F6_5370_484D_A727_F15C776309C6 */
