#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <functional>
namespace math {

struct Constant {
    Constant() = delete;
    static inline constexpr double pi = 3.14159265;
    static inline constexpr double e = 2.71828183;
};

class Graph {
public:
    Graph(sf::Vector2<double> domain, std::function<double(double)> func, unsigned int intervals);
    void update(sf::Vector2<double> domain, std::function<double(double)> func, unsigned int intervals);
    
    const std::vector<sf::Vector2<double>>& getData();    
    sf::Vector2<double> getDomain();
    sf::Vector2<double> getRange();
    std::function<double(double)> getFunction();

private:
    std::vector<sf::Vector2<double>> m_graph;
    sf::Vector2<double> m_domain;
    sf::Vector2<double> m_range;
    std::function<double(double)> m_func;
};

} // namespace math