#ifndef SORT_H
#define SORT_H

#include <SFML/Graphics.hpp>
#include <array>

#define MAX_ARRAY_SIZE 1000

enum sortAlgorithms
{
    bubble_sort
};

class Sort
{
    public:
        std::array<uint16_t, MAX_ARRAY_SIZE> data;
        std::array<sf::RectangleShape, MAX_ARRAY_SIZE> shapes;
        int arraySize;
        sortAlgorithms chosenAlgorithm;
        unsigned rng_seed;
        Sort(sf::Vector2u screenSize, int arraySize, sortAlgorithms algorithm_choice);
        void doSort();
        void shuffle(sf::Vector2u screenSize);
        void generateSeed();

    private:
        void bubbleSort();
};

#endif
