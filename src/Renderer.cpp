#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "Sort.h"
#include <iostream>
#include <thread>

Renderer::Renderer()
    : sort(sf::Vector2u(MIN_WIN_SIZE_X, MIN_WIN_SIZE_Y), TITLE_HEIGHT, bubble_sort)
{
    window.setVerticalSyncEnabled(true); // framerate will match the screens refresh rate
    titleBarInit();
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
                title_bar.setSize(sf::Vector2f(event.size.width, TITLE_HEIGHT));
                sort.shape_from_num(sf::Vector2u(event.size.width, event.size.height), TITLE_HEIGHT); // update size/position of shapes to fit new screen
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
                            sort.shuffle();
                        }
                        break;

                    case sf::Keyboard::Scan::Num1: // bubble sort selected
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

    // render title block
    window.draw(title_bar);

    // update rect positions based on sort algorithm
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        window.draw(sort.shapes[i].rect);

    window.display(); // write to the screen
}

void Renderer::titleBarInit()
{
    title_bar.setFillColor(sf::Color::White);
    title_bar.setPosition(0, 0);
    title_bar.setSize(sf::Vector2f(MIN_WIN_SIZE_X, TITLE_HEIGHT));
}
