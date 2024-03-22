#ifndef SORT_H
#define SORT_H

#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>

#define MAX_ARRAY_SIZE 1000

enum sortAlgorithms
{
    bubble_sort
};

struct Shape 
{
    sf::RectangleShape rect;
    uint16_t num;

    // swap func based on num
    void swap(Shape& other)
    {
        std::swap(num, other.num);
    }

    // overload for <
    friend bool operator<(const Shape& s1, const Shape& s2)
    {
        return s1.num < s2.num;
    }

    // overload for ==
    friend bool operator==(const Shape& s1, const Shape& s2)
    {
        return s1.num == s2.num;
    }
};

class Sort
{
    public:
        std::array<Shape, MAX_ARRAY_SIZE> shapes;
        int arraySize;
        sortAlgorithms chosenAlgorithm;
        unsigned rng_seed;
        Sort(sf::Vector2u screenSize, int arraySize, sortAlgorithms algorithm_choice);
        void doSort();
        void shuffle(sf::Vector2u screenSize);
        void generateSeed();
        friend void swap(Shape& s1, Shape& s2);
        void shape_from_num(sf::Vector2u screenSize);

    private:
        void bubbleSort();
};

#endif
