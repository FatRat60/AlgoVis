#include <iostream>
#include <SFML/Window.hpp>

int main(int, char**)
{
    sf::Window window(sf::VideoMode(800, 600), "Test");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
