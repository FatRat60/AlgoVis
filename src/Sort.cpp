#include "Sort.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <array>
#include <iostream>
#include <thread>

Sort::Sort(sf::Vector2u screenSize, sortAlgorithms algorithm_choice)
{
    std::cout << "sort init\n";
    killThread = false;
    canRead = true;
    sortDone = false;
    chosenAlgorithm = algorithm_choice;
    // init array

    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        // only set num. RectangleShape will be init from num in shape_from_num()
        shapes[i].num = i+1;
    }

    shape_from_num(screenSize);
    // shufle data
    shuffle(screenSize);
}

void Sort::shuffle(sf::Vector2u screenSize)
{
    generateSeed();
    std::shuffle(shapes.begin(), shapes.end(), std::default_random_engine(rng_seed));

    // update shapes
    //shape_from_num(screenSize);
}

void Sort::generateSeed()
{
    rng_seed = std::chrono::system_clock::now().time_since_epoch().count();
}

void swap(Shape& s1, Shape& s2)
{
    s1.swap(s2);
}

void Sort::shape_from_num(sf::Vector2u screenSize)
{
    float heightInc = float(screenSize.y) / MAX_ARRAY_SIZE;
    float width = float(screenSize.x) / MAX_ARRAY_SIZE;
    float line_thickness = width * -0.10;

    // init shapes
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        Shape *cur = &shapes[i];
        float height = heightInc * cur->num;
        cur->rect.setFillColor(sf::Color::White);
        cur->rect.setOutlineColor(sf::Color::Black);
        cur->rect.setOutlineThickness(line_thickness);
        cur->rect.setSize(sf::Vector2f(width, height));
        cur->rect.setPosition(sf::Vector2f(i * width, screenSize.y - height));
    }
}

void Sort::doSort()
{
    switch (chosenAlgorithm)
    {
    case bubble_sort:
        std::cout << "Doing bubble\n";
        bubbleSort();
        break;
    
    default:
        break;
    }
    std::cout << "done sorting!\n";
    sortDone = !killThread; // set sortDOne to true only if thread wasnt killed
}

void Sort::bubbleSort()
{
    bool didSwap = true;
    int end_point = MAX_ARRAY_SIZE - 1;
    while (didSwap && !killThread)
    {
        didSwap = false;
        for (int i = 0; i < end_point; i++)
        {
            shapes[i].rect.setFillColor(sf::Color::Red);
            shapes[i+1].rect.setFillColor(sf::Color::Red);
            std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY)); // delay sort
            // found a pair out of order
            if (shapes[i+1] < shapes[i])
            {
                didSwap = true;
                swap(shapes[i], shapes[i+1]);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY)); // delay sort
            shapes[i].rect.setFillColor(sf::Color::White);
            shapes[i+1].rect.setFillColor(sf::Color::White);
        }
        end_point--;
    }
    if (killThread)
        std::cout << "Thread killed\n";
    if (!didSwap)
        std::cout << "bubble finished\n";
}
