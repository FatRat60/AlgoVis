#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main(int, char**)
{
    // create window in main thread
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "Test");
    window->setVerticalSyncEnabled(true); // framerate will match the screens refresh rate

    // TODO: Create graphics thread
    window->setActive(false);
    Renderer renderer(window);
    std::cout << "Garsh\n";
    renderer.EventLoop();
    
    return 0;
}
