#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <functional>

struct Constant {
    Constant() = delete;
    static inline constexpr double pi = 3.14159265;
    static inline constexpr double e = 2.71828183;
};

class Graph {
public:
    Graph();
    Graph(sf::Vector2<double> domain, std::function<double(double)> func, unsigned int subints);
    void update(sf::Vector2<double> domain, std::function<double(double)> func, unsigned int subints);
    
    const std::vector<sf::Vector2<double>> getPoints() const; 
    sf::Vector2<double> getDomain() const;
    sf::Vector2<double> getRange() const;
    std::function<double(double)> getFunction() const;
    double getWidth() const;
    double getHeight() const;
    int getSubintervals() const;

private:
    std::vector<sf::Vector2<double>> m_points;
    sf::Vector2<double> m_domain;
    sf::Vector2<double> m_range;
    std::function<double(double)> m_func;
};