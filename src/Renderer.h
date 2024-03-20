#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <array>

class Renderer
{
    public:
        sf::RenderWindow *window;
        std::array<int, 1000> data;
        Renderer(sf::RenderWindow *window);
        void EventLoop();

    private:
        void doDraw();
};

#endif