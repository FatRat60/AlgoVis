#ifndef SORT_H
#define SORT_H

#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include <array>

#define MAX_ARRAY_SIZE 1000

enum sortAlgorithms
{
    bubble_sort
};

class Sort
{
    public:
        std::array<sf::RectangleShape, MAX_ARRAY_SIZE> data;
        sortAlgorithms chosenAlgorithm;
        unsigned int rng_seed;
        Sort(sf::Vector2u screenSize, int arraySize, sortAlgorithms algorithm_choice);
        void doSort();
        void shuffle();
        void generateSeed();
    private:
        void bubbleSort();
};

#endif
