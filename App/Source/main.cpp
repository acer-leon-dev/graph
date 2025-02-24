#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "graphing/math.hpp"
#include "mapping.hpp"

math::number example_function(math::number x) {
    return std::sin(x);
}
 
int main(int argc, char* argv[])
{

    math::Graph graph{{0, 2 * math::constant::pi}, 48, example_function};
    graph.print();

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Graphing App");
 
    // Load a sprite to display
    const sf::CircleShape circle(100, 20);
 
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
 
        // Clear screen
        window.clear();
 
        // Draw the sprite
        window.draw(circle);
 
        // Update the window
        window.display();
    }
}