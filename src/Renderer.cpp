#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "Sort.h"
#include <iostream>
#include <thread>

Renderer::Renderer(sf::RenderWindow *w, int arraySize, sortAlgorithms algorithm_choice)
    : sort(w->getSize(), arraySize, algorithm_choice)
{
    window = w;
    window->setVerticalSyncEnabled(true); // framerate will match the screens refresh rate
}

Renderer::~Renderer()
{
    if (sortThread.joinable())
    {
        sort.killThread = true;
        sortThread.join();
    }
    delete window;
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
            case sf::Event::Resized:
                sort.shape_from_num(sf::Vector2u(event.size.width, event.size.height)); // update size/position of shapes to fit new screen
                break;
            case sf::Event::KeyReleased:
                if (event.key.scancode == sf::Keyboard::Scan::Space && !sortThread.joinable()){
                    std::cout << "Beginning Sort!\n";
                    //sortThread = std::thread(&Sort::doSort, std::ref(sort)); // spawn the sorting thread
                    sort.shuffle(window->getSize());
                }
                break;
            
            default:
                break;
            }
        }
        doDraw();
    }
    std::cout << "Window Closed\n";
}

void Renderer::doDraw()
{
    window->clear(sf::Color::Black); // clear the screen

    // update rect positions based on sort algorithm

    for (Shape shape : sort.shapes)
        window->draw(*shape.rect);

    window->display(); // write to the screen
}
