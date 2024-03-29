#ifndef SORT_H
#define SORT_H

#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>

#define MAX_ARRAY_SIZE 100
#define SORT_DELAY 5

enum sortAlgorithms
{
    bubble_sort,
    merge_sort,
    selection_sort,
    insertion_sort
};

struct Shape 
{
    sf::RectangleShape rect;
    uint16_t num;

    // swap func based on num
    void swap(Shape& other)
    {
        
        std::swap(num, other.num);
        swapPos(other);
    }

    void swapPos(Shape& other)
    {
        // get old positions
        sf::Vector2f curPos = rect.getPosition();
        sf::Vector2f otherPos = other.rect.getPosition();
        std::swap(curPos.x, otherPos.x);
        rect.setPosition(curPos);
        other.rect.setPosition(otherPos);
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
        sortAlgorithms chosenAlgorithm;
        unsigned rng_seed;
        bool killThread;
        bool canRead;
        bool sortDone;
        int numSwaps;
        int numArrayAccess;
        Sort(sf::Vector2u screenSize, int title_height, sortAlgorithms algorithm_choice);
        void doSort();
        void shuffle();
        void generateSeed();
        void paws(Shape& s1, Shape& s2); // extra layer for swap to inc numSwaps
        friend void swap(Shape& s1, Shape& s2);
        void shape_from_num(sf::Vector2u screenSize, int title_height);
        Shape& accessArray(int index);

    private:
        void initShapeCopy(Shape *copy, Shape *original);
        void win();
        void bubbleSort();
        void mergeSort(int left, int right);
        void merge(int left, int middle, int right);
        void selectionSort();
        void insertionSort();
};

#endif
