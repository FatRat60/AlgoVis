#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>
#include <chrono>
#include <array>
#include <iostream>

Renderer::Renderer(sf::RenderWindow *w)
{
    window = w;
    // initialize 
    for (int i = 0; i < 1000; i++)
    {
        data[i] = i+1;
    }
    // shuffle the array
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(data.begin(), data.end(), std::default_random_engine(seed));
}

void Renderer::EventLoop()
{
    window->setActive(true); // activate window in current thread
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            
            default:
                break;
            }
        }

        doDraw();
    }
    std::cout << "BAI BAI\n";
    // free window
    delete window;
}

void Renderer::doDraw()
{
    window->clear(sf::Color::Black); // clear the screen

    //window->draw()

    window->display(); // write to the screen
}