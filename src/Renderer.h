#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Sort.h"
#include <thread>

#define MIN_WIN_SIZE_X 800
#define MIN_WIN_SIZE_Y 600
#define TITLE_HEIGHT 20

class Renderer
{
    public:
        sf::RenderWindow window;
        sf::Font font;
        sf::Text title_text;
        sf::Text repo_text;
        Sort sort;
        std::thread sortThread;
        bool showStats;
        Renderer();
        void EventLoop();

    private:
        void titleTextInit();
        void doDraw();
        std::string cleanTitle();
        template<typename ... Args>
        std::string string_format(const std::string& format, Args ... args);
};

#endif
