#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "Sort.h"
#include <iostream>

Renderer::Renderer(sf::RenderWindow *w, int arraySize, sortAlgorithms algorithm_choice)
    : sort(arraySize, algorithm_choice)
{
    window = w;
    window->setVerticalSyncEnabled(true); // framerate will match the screens refresh rate

    // init array
    if (arraySize > MAX_ARRAY_SIZE || arraySize < 0)
        arraySize = MAX_ARRAY_SIZE;
    sf::Vector2u screenSize = w->getSize();
    float width = float(screenSize.x) / arraySize;
    float heightInc = float(screenSize.y) / arraySize;

    // init shapes
    for (int i = 0; i < arraySize; i++)
    {
        shapes[i].setFillColor(sf::Color::White);
        shapes[i].setSize(sf::Vector2f(width, heightInc * sort.data[i]));
        shapes[i].setPosition(sf::Vector2f(i * width, screenSize.y - heightInc * sort.data[i]));
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
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyReleased:
                if (event.key.scancode == sf::Keyboard::Scan::Space){
                    shuffle();
                }
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

void Renderer::shuffle()
{
    // first shuffle dummy area in sort
    sort.shuffle();
    // then update shapes heights
    sf::Vector2u screenSize = window->getSize();
    float heightInc = float(screenSize.y) / sort.arraySize; // this MIGHT return 1000 instead of the acutal num
    for (int i = 0; i < sort.arraySize; i++)
    {
        float len = heightInc * sort.data[i];
        float x = shapes[i].getSize().x;
        shapes[i].setSize(sf::Vector2f(x, len));
        x = shapes[i].getPosition().x;
        shapes[i].setPosition(sf::Vector2f(x, screenSize.y - len));
    }
}

void Renderer::doDraw()
{
    window->clear(sf::Color::Black); // clear the screen

    // update rect positions based on sort algorithm

    for (sf::RectangleShape shape : shapes)
        window->draw(shape);

    window->display(); // write to the screen
}
