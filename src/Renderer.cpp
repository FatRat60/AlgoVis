#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "Sort.h"
#include <iostream>
#include <thread>

Renderer::Renderer(sf::RenderWindow *w, sortAlgorithms algorithm_choice)
    : sort(w->getSize(), algorithm_choice)
{
    window = w;
    window->setVerticalSyncEnabled(true); // framerate will match the screens refresh rate
}

Renderer::~Renderer()
{
    std::cout << "deleting Sort\n";
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
                switch (event.key.scancode)
                {
                    case sf::Keyboard::Scan::R:
                        if (!sortThread.joinable())
                        {
                            sort.shuffle(window->getSize());
                        }
                        break;
                    case sf::Keyboard::Scan::Space:
                        if (!sortThread.joinable())
                        {
                            std::cout << "Beginning Sort!\n";
                            sortThread = std::thread(&Sort::doSort, std::ref(sort)); // spawn the sorting thread
                        }
                        break;
                }
                break;
            
            default:
                break;
            }
        }
        if (sort.canRead)
            doDraw();
        if (sort.sortDone)
        {
            sort.sortDone = false;
            sortThread.join();
        }
    }
    std::cout << "Window Closed\n";
}

void Renderer::doDraw()
{
    window->clear(sf::Color::Black); // clear the screen

    // update rect positions based on sort algorithm
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        window->draw(sort.shapes[i].rect);

    window->display(); // write to the screen
}
