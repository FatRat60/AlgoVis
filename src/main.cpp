#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sort.h"

int main(int, char**)
{
    // validate user input
    int arraySize = 600;
    sortAlgorithms algorithm_choice = bubble_sort;

    // create window in main thread
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "Test");

    // TODO: Create sorting thread
    Renderer renderer(window, arraySize, algorithm_choice);
    
    renderer.EventLoop();
    return 0;
}
