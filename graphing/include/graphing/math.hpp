#pragma once
#include <vector>

namespace math {

typedef double number;
typedef long long int integer;

struct point {
    number x;
    number y;

    void print();
};

struct domain {
    number low;
    number high;

    void print();
};

struct range {
    number low;
    number high;

    void print();
};

struct constant {
    constant() = delete;
    static inline constexpr number pi = 3.14159265;
    static inline constexpr number e = 2.71828183;
};

class Graph {
public:
    Graph(domain d, unsigned int intervals, number (*func)(number));
    void update(domain d, unsigned int intervals, number (*func)(number));

    void print();
    
    const std::vector<point>& get_data();
    
    domain get_domain();
    range get_range();
    
private:
    domain m_domain;
    range m_range;
    std::vector<point> m_graph;
};

} // namespace math