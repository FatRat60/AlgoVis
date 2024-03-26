#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sort.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // Check num of args
    if (argc < 2)
    {
        std::cout << "Usage: AlgoVis <algorithm choice: 0-0>\n";
        exit(1);
    }

    // validate user input
    int arraySize = atoi(argv[1]);
    int algo = atoi(argv[2]);
    sortAlgorithms algorithm_choice;
    if (algo >= 0 && algo < IMPLEMENTED_SORTS)
        algorithm_choice = sortAlgorithms(algo);
    else
    {
        std::cout << "Usage: AlgoVis <algorithm choice: 0-0>\n";
        exit(1);
    }

    // create window in main thread
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "Test");

    // TODO: Create sorting thread
    Renderer renderer(window, algorithm_choice);
    
    renderer.EventLoop();
    return 0;
}
