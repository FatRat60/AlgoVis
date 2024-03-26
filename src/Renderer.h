#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Sort.h"
#include <thread>

#define MIN_WIN_SIZE_X 800
#define MIN_WIN_SIZE_Y 600
#define TITLE_HEIGHT 50

class Renderer
{
    public:
        sf::RenderWindow window;
        sf::RectangleShape title_bar;
        sf::Font font;
        sf::Text title_text;
        Sort sort;
        std::thread sortThread;
        Renderer();
        void EventLoop();

    private:
        void titleBarInit();
        void titleTextInit();
        void doDraw();
};

#endif
