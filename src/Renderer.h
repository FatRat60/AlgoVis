#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Sort.h"

class Renderer
{
    public:
        sf::RenderWindow *window;
        Sort sort;
        Renderer(sf::RenderWindow *window, int arraySize, sortAlgorithms chosen_algorithm);
        void EventLoop();

    private:
        void doDraw();
};

#endif
