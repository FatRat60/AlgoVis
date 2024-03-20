#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <array>

#define MAX_ARRAY_SIZE 1000

class Renderer
{
    public:
        sf::RenderWindow *window;
        std::array<sf::RectangleShape, MAX_ARRAY_SIZE> shapes;
        float size;
        Renderer(sf::RenderWindow *window, std::array<int, MAX_ARRAY_SIZE> &data);
        void EventLoop();

    private:
        void doDraw();
};

#endif