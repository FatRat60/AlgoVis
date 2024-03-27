#include "Sort.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <array>
#include <iostream>
#include <thread>

Sort::Sort(sf::Vector2u screenSize, int title_height, sortAlgorithms algorithm_choice)
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

    shape_from_num(screenSize, title_height);
    // shufle data
    shuffle();
}

void Sort::shuffle()
{
    generateSeed();
    std::shuffle(shapes.begin(), shapes.end(), std::default_random_engine(rng_seed));
}

void Sort::generateSeed()
{
    rng_seed = std::chrono::system_clock::now().time_since_epoch().count();
}

void swap(Shape& s1, Shape& s2)
{
    s1.swap(s2);
}

void Sort::shape_from_num(sf::Vector2u screenSize, int title_height)
{
    float heightInc = float(screenSize.y - title_height) / MAX_ARRAY_SIZE;
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

    case merge_sort:
        std::cout << "Doing merge\n";
        mergeSort(0, MAX_ARRAY_SIZE);
        break;

    case selection_sort:
        selectionSort();
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

void Sort::mergeSort(int left, int right)
{
    // base case
    if (right - left < 2)
        return;
    
    int midpoint = (right - left) / 2;

    std::cout << "go Left\n";
    mergeSort(left, midpoint);

    std::cout << "go Right\n";
    mergeSort(midpoint + 1, right);

    // merge values
    std::cout << "Merge!\n";
    merge(left, midpoint, right);
}

void Sort::merge(int left, int middle, int right)
{
    std::cout << "SIZE: " << right - left << "\nMiddle: " << middle << "\n";
    int k = 0;
    int SIZE = right - left;
    Shape temp[SIZE];
    int left_start = left;
    std::cout << "Left Start: " << left_start << "\n";
    int right_start = right;
    std::cout << "Right Start: " << right_start << "\n";
    // sort values into temp array
    while (left_start <= middle && right_start < right)
    {
        if (shapes[left_start] < shapes[right_start])
        {
            temp[k++] = shapes[left_start++];
        }
        else 
        {
            temp[k++] = shapes[right_start++];
        }
    }
    // write remaining values from either left or right
    if (left_start <= middle)
    {
        for (int i = left_start; i <= middle; i++)
        {
            temp[k++] = shapes[i];
        }
    }
    else
    {
        for (int i = right_start; i < right; i++)
        {
            temp[k++] = shapes[i];
        }
    }

    // copy from temp back to shapes
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << "shapes[" << i+left << "] = temp[" << i << "]\n";
        shapes[i+left] = temp[i];
    }
    std::cout << " End merge\n";
}

void Sort::selectionSort()
{
    int start = 0;
    while (start < MAX_ARRAY_SIZE && !killThread)
    {
        Shape *lowest = &shapes[start];
        int swapIndex = start;
        lowest->rect.setFillColor(sf::Color::Red);
        for (int i = start + 1; i < MAX_ARRAY_SIZE; i++)
        {
            shapes[i].rect.setFillColor(sf::Color::Red);
            std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY)); // delay sort
            if (shapes[i] < *lowest)
            {
                lowest->rect.setFillColor(sf::Color::White);
                shapes[start].rect.setFillColor(sf::Color::Red);
                lowest = &shapes[i];
                swapIndex = i;
            }
            else
            {
                shapes[i].rect.setFillColor(sf::Color::White);
            }
        }
        swap(shapes[start], shapes[swapIndex]);
        shapes[start].rect.setFillColor(sf::Color::White);
        lowest->rect.setFillColor(sf::Color::White);
        start++;
    }
}