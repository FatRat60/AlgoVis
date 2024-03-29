#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Sort.h"
#include <thread>

// cross platform implementations of opening url
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define OpenURL(url) system("start " url);
#elif __APPLE__
#define OpenURL(url) system("open " url);
#elif __linux__
#define OpenURL(url) system("xdg-open" url);
#else
#error "Unknown compiler"
#endif


#define MIN_WIN_SIZE_X 800
#define MIN_WIN_SIZE_Y 600
#define TITLE_HEIGHT 20
#define GITHUB_URL "https://github.com/FatRat60/AlgoVis"

class Renderer
{
    public:
        sf::RenderWindow window;
        sf::Image icon;
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
