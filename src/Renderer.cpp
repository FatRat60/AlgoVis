#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "Sort.h"
#include <iostream>
#include <thread>

Renderer::Renderer()
    : sort(sf::Vector2u(MIN_WIN_SIZE_X, MIN_WIN_SIZE_Y), bubble_sort)
{
    window.setVerticalSyncEnabled(true); // framerate will match the screens refresh rate
}

void Renderer::EventLoop()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                sort.killThread = sortThread.joinable();
                break;

            case sf::Event::Resized:
                if (event.size.width < MIN_WIN_SIZE_X || event.size.height < MIN_WIN_SIZE_Y)
                {
                    event.size.width = MIN_WIN_SIZE_X;
                    event.size.height = MIN_WIN_SIZE_Y;
                    window.setSize(sf::Vector2u(event.size.width, event.size.height));
                }
                sort.shape_from_num(sf::Vector2u(event.size.width, event.size.height)); // update size/position of shapes to fit new screen
                break;

            case sf::Event::KeyReleased:
                switch (event.key.scancode)
                {
                    case sf::Keyboard::Scan::K:
                        sort.killThread = sortThread.joinable(); 
                        break;

                    case sf::Keyboard::Scan::R:
                        if (!sortThread.joinable())
                        {
                            sort.shuffle(window.getSize());
                        }
                        break;

                    case sf::Keyboard::Scan::Space:
                        if (!sortThread.joinable())
                        {
                            std::cout << "Beginning Sort!\n";
                            sortThread = std::thread(&Sort::doSort, std::ref(sort)); // spawn the sorting thread
                        }
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
            }
        }
        
        doDraw();

        if (sort.sortDone || sort.killThread)
        {
            sort.sortDone = false;
            sortThread.join();
            sort.killThread = false;
        }
    }
    std::cout << "Window Closed\n";
}

void Renderer::doDraw()
{
    window.clear(sf::Color::Black); // clear the screen

    // update rect positions based on sort algorithm
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        window.draw(sort.shapes[i].rect);

    window.display(); // write to the screen
}
