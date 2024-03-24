#include "Sort.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <array>
#include <iostream>

Sort::Sort(sf::Vector2u screenSize, int arraySize, sortAlgorithms algorithm_choice)
{
    // init array
    if (arraySize > MAX_ARRAY_SIZE || arraySize < 0)
        arraySize = MAX_ARRAY_SIZE;
    this->arraySize = arraySize;

    for (int i = 0; i < arraySize; i++)
    {
        // only set num. RectangleShape will be init from num in shape_from_num()
        shapes[i].num = i+1;
    }
    // shufle data
    shuffle(screenSize);
}

void Sort::shuffle(sf::Vector2u screenSize)
{
    generateSeed();
    std::shuffle(shapes.begin(), shapes.end(), std::default_random_engine(rng_seed));

    // update shapes
    shape_from_num(screenSize);
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
    float heightInc = float(screenSize.y) / arraySize;
    float width = float(screenSize.x) / arraySize;

    // init shapes
    for (int i = 0; i < arraySize; i++)
    {
        Shape *cur = &shapes[i];
        float height = heightInc * cur->num;
        cur->rect.setFillColor(sf::Color::White);
        cur->rect.setSize(sf::Vector2f(width, height));
        cur->rect.setPosition(sf::Vector2f(i * width, screenSize.y - height));
    }
}

void Sort::doSort()
{
    switch (chosenAlgorithm)
    {
    case bubble_sort:
        bubbleSort();
        break;
    
    default:
        break;
    }
}

void Sort::bubbleSort()
{
    
}
