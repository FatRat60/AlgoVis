#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>
#include <chrono>
#include <array>
#include <iostream>

Renderer::Renderer(sf::RenderWindow *w, std::array<int, MAX_ARRAY_SIZE> &data)
{
    window = w;
    size = 0.8;
    // create rectangles
    sf::Vector2u screenSize = w->getSize();
    float width = float(screenSize.x) / MAX_ARRAY_SIZE;
    float heightInc = float(screenSize.y) / MAX_ARRAY_SIZE;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
         //shapes[i] = sf::RectangleShape(sf::Vector2f(width, heightInc * data[i]));
         shapes[i].setSize(sf::Vector2f(width, heightInc * data[i]));
         shapes[i].setFillColor(sf::Color::White);
         shapes[i].setPosition(sf::Vector2f(i * width, screenSize.y - heightInc * data[i]));
    }
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
                    size += 0.8;
                    std::cout << size << "\n";
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

    for (sf::RectangleShape shape : shapes)
        window->draw(shape);

    window->display(); // write to the screen
}