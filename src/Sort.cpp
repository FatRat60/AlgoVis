#include "Sort.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <array>
#include <iostream>

Sort::Sort(int arraySize, sortAlgorithms algorithm_choice)
{
    // init array
    if (arraySize > MAX_ARRAY_SIZE || arraySize < 0)
        arraySize = MAX_ARRAY_SIZE;
    this->arraySize = arraySize;

    for (int i = 0; i < arraySize; i++)
    {
        data[i] = i+1;
    }
    // shufle data
    shuffle();
}

void Sort::shuffle()
{
    generateSeed();
    std::shuffle(data.begin(), data.end(), std::default_random_engine(rng_seed));
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
