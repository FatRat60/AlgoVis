#include "Sort.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <array>
#include <iostream>
#include <thread>

Sort::Sort(sf::Vector2u screenSize, int title_height, sortAlgorithms algorithm_choice)
{
    killThread = false;
    canRead = true;
    sortDone = false;
    chosenAlgorithm = algorithm_choice;
    numSwaps = 0;
    numArrayAccess = 0;
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

void Sort::paws(Shape& s1, Shape& s2)
{
    numSwaps += 1; // inc swap cnt
    s1.swap(s2); // actually do swap
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

Shape& Sort::accessArray(int index)
{
    numArrayAccess += 1;
    return shapes[index];
}

void Sort::doSort()
{
    switch (chosenAlgorithm)
    {
    case bubble_sort:
        bubbleSort();
        break;

    case merge_sort:
        mergeSort(0, MAX_ARRAY_SIZE);
        break;

    case selection_sort:
        selectionSort();
        break;

    case insertion_sort:
        insertionSort();
        break;
    
    default:
        break;
    }

    if (!killThread) // dont play animation if thread is killed
    {
        win();
    }
}

void Sort::initShapeCopy(Shape *copy, Shape *original)
{
    copy->num = original->num;
    copy->rect.setFillColor(original->rect.getFillColor());
    copy->rect.setPosition(original->rect.getPosition());
    copy->rect.setSize(original->rect.getSize());
    copy->rect.setOutlineColor(original->rect.getOutlineColor());
    copy->rect.setOutlineThickness(original->rect.getOutlineThickness());
}

void Sort::win()
{
    // slowly iterate thru shapes and turn them green
        for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        {
            shapes[i].rect.setFillColor(sf::Color::Green);
            std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY)); // delay sort
        }
        sortDone = true;
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
            if (accessArray(i+1) < accessArray(i))
            {
                didSwap = true;
                paws(accessArray(i), accessArray(i+1));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY)); // delay sort
            shapes[i].rect.setFillColor(sf::Color::White);
            shapes[i+1].rect.setFillColor(sf::Color::White);
        }
        end_point--;
    }
}

void Sort::mergeSort(int left, int right)
{
    // base case
    if (right - left < 2){
        shapes[left].rect.setFillColor(sf::Color::Red);
        std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY)); // delay sort
        shapes[left].rect.setFillColor(sf::Color::White);
        return;
    }
    
    int midpoint = left + (right - left) / 2;

    mergeSort(left, midpoint);

    mergeSort(midpoint, right);

    // merge values
    merge(left, midpoint, right);
}

void Sort::merge(int left, int middle, int right)
{
    int k = 0;
    int SIZE = right - left;
    Shape temp[SIZE];
    int left_start = left;
    int right_start = middle;
    // sort values into temp array
    while (left_start < middle && right_start < right)
    {
        Shape *original;
        if (accessArray(left_start) < accessArray(right_start))
        {
            original = &accessArray(left_start++);
        }
        else 
        {
            original = &accessArray(right_start++);
        }
        initShapeCopy(&temp[k++], original);
        numArrayAccess++; // inc cuz temp accessed
    }
    // write remaining values from either left or right
    if (left_start < middle)
    {
        for (int i = left_start; i < middle; i++)
        {
            initShapeCopy(&temp[k++], &accessArray(i));
            numArrayAccess++;
        }
    }
    else
    {
        for (int i = right_start; i < right; i++)
        {
            initShapeCopy(&temp[k++], &accessArray(i));
            numArrayAccess++;
        }
    }

    // copy from temp back to shapes
    for (int i = 0; i < SIZE; i++)
    {
        paws(accessArray(i+left), temp[i]);
        numArrayAccess++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY * 2)); // delay sort
}

void Sort::selectionSort()
{
    int start = 0;
    while (start < MAX_ARRAY_SIZE && !killThread)
    {
        int swapIndex = start;
        shapes[swapIndex].rect.setFillColor(sf::Color::Red);
        for (int i = start + 1; i < MAX_ARRAY_SIZE; i++)
        {
            shapes[i].rect.setFillColor(sf::Color::Red);
            std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY)); // delay sort
            if (accessArray(i) < accessArray(swapIndex))
            {
                shapes[swapIndex].rect.setFillColor(sf::Color::White);
                shapes[start].rect.setFillColor(sf::Color::Red);
                swapIndex = i;
            }
            else
            {
                shapes[i].rect.setFillColor(sf::Color::White);
            }
        }
        paws(accessArray(start), accessArray(swapIndex));
        shapes[start].rect.setFillColor(sf::Color::White);
        shapes[swapIndex].rect.setFillColor(sf::Color::White);
        start++;
    }
}

void Sort::insertionSort()
{
    for (int i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        if (killThread)
            break;
        shapes[i].rect.setFillColor(sf::Color::Red);
        Shape key;
        initShapeCopy(&key, &accessArray(i));
        int j = i - 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY) / 2); // delay sort
        while (j >= 0 && key < accessArray(j))
        {
            shapes[j].rect.setFillColor(sf::Color::Red);
            std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY) / 2); // delay sort
            paws(accessArray(j+1), accessArray(j));
            shapes[j].rect.setFillColor(sf::Color::White);
            j--;
        }
        paws(accessArray(j+1), key);
        shapes[j+1].rect.setFillColor(sf::Color::White);
        std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY) / 2); // delay sort
    }
}