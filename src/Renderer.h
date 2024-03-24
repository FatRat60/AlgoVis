#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Sort.h"
#include <thread>

class Renderer
{
    public:
        sf::RenderWindow *window;
        Sort sort;
        std::thread sortThread;
        Renderer(sf::RenderWindow *window, int arraySize, sortAlgorithms chosen_algorithm);
        ~Renderer();
        void EventLoop();

    private:
        void doDraw();
};

#endif
