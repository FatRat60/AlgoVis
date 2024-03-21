#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "Sort.h"
#include <iostream>

Renderer::Renderer(sf::RenderWindow *w, int arraySize, sortAlgorithms algorithm_choice)
{
    window = w;
    window->setVerticalSyncEnabled(true); // framerate will match the screens refresh rate
    
}

void Renderer::EventLoop()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                if (event.key.scancode == sf::Keyboard::Scan::Space){
                    sort.shuffle();
                }
                break;
            case sf::Event::Closed:
                window->close();
                break;
            
            default:
                break;
            }
        }
        doDraw();
    }
    // free window
    delete window;
}

void Renderer::doDraw()
{
    window->clear(sf::Color::Black); // clear the screen

    // update rect positions based on sort algorithm

    for (sf::RectangleShape shape : sort.data)
        window->draw(shape);

    window->display(); // write to the screen
}
