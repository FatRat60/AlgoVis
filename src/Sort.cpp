#include "Sort.h"
#include <random>
#include <algorithm>
#include <chrono>

Sort::Sort(sf::Vector2u screenSize, int arraySize, sortAlgorithms algorithm_choice)
{
    // init array
    if (arraySize > MAX_ARRAY_SIZE || arraySize < 0)
        arraySize = MAX_ARRAY_SIZE;
    float width = float(screenSize.x) / MAX_ARRAY_SIZE;
    float heightInc = float(screenSize.y) / MAX_ARRAY_SIZE;
    for (int i = 0; i < arraySize; i++)
    {
        int num = i + 1;
        data[i].setFillColor(sf::Color::White);
        data[i].setSize(sf::Vector2f(width, heightInc * num));
        data[i].setPosition(sf::Vector2f(i * width, screenSize.y - heightInc * num));
    }
    // init random stuff
    generateSeed();
    // shufle data
    shuffle();
}

void Sort::shuffle()
{
    std::shuffle(data.begin(), data.end(), rng_seed);
}

void Sort::generateSeed()
{
    rng_seed = std::chrono::system_clock::now().time_since_epoch().count();
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
