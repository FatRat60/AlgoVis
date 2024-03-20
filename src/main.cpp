#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

int main(int, char**)
{
    // create window in main thread
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "Test");
    window->setVerticalSyncEnabled(true); // framerate will match the screens refresh rate

    //create array
    std::array<int, MAX_ARRAY_SIZE> data;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        data[i] = i+1;
    }
    // shuffle the array
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(data.begin(), data.end(), std::default_random_engine(seed));

    // TODO: Create sorting thread
    Renderer renderer(window, data);
    
    renderer.EventLoop();
    return 0;
}
