#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Sort.h"
#include <thread>

#define MIN_WIN_SIZE_X 800
#define MIN_WIN_SIZE_Y 600

class Renderer
{
    public:
        sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(MIN_WIN_SIZE_X, MIN_WIN_SIZE_Y), "Algorithm Visualizer");
        Sort sort;
        std::thread sortThread;
        Renderer();
        void EventLoop();

    private:
        void doDraw();
};

#endif
