#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "Graph/math.hpp"

number example_function(number x) {
    return std::sin(x);
}

int main() {
    std::cout << "Hello Math!\n";

    Graph graph{{0, 2 * constant::pi}, 48, example_function};
    graph.print();
}