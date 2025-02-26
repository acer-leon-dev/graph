#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

namespace math {

typedef double number;
typedef long long int integer;

struct constant {
    constant() = delete;
    static inline constexpr number pi = 3.14159265;
    static inline constexpr number e = 2.71828183;
};

class Graph {
public:
    Graph(sf::Vector2<number> d, unsigned int intervals, number (*func)(number));
    void update(sf::Vector2<number> d, unsigned int intervals, number (*func)(number));

    void print();
    
    const std::vector<sf::Vector2<number>>& get_data();
    
    sf::Vector2<number> get_domain();
    sf::Vector2<number> get_range();
    
private:
    sf::Vector2<number> m_domain;
    sf::Vector2<number> m_range;
    std::vector<sf::Vector2<number>> m_graph;
};

} // namespace math