#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "Sort.h"
#include <iostream>
#include <thread>

Renderer::Renderer()
    : sort(sf::Vector2u(MIN_WIN_SIZE_X, MIN_WIN_SIZE_Y), TITLE_HEIGHT, bubble_sort),
    window(sf::VideoMode(MIN_WIN_SIZE_X, MIN_WIN_SIZE_Y), "Algorithm Visualizer")
{
    window.setVerticalSyncEnabled(true); // framerate will match the screens refresh rate
    // init font
    if (!font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "Could not load font!\n";
        exit(1);
    }
    titleTextInit();
    showStats = false;
}

void Renderer::EventLoop()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                sort.killThread = sortThread.joinable();
                break;

            case sf::Event::Resized:
                if (event.size.width < MIN_WIN_SIZE_X || event.size.height < MIN_WIN_SIZE_Y)
                {
                    event.size.width = MIN_WIN_SIZE_X;
                    event.size.height = MIN_WIN_SIZE_Y;
                    window.setSize(sf::Vector2u(event.size.width, event.size.height));
                }
                sort.shape_from_num(sf::Vector2u(event.size.width, event.size.height), TITLE_HEIGHT); // update size/position of shapes to fit new screen
                break;

            case sf::Event::KeyReleased:
                // commands usable while not sorting
                if (!sortThread.joinable())
                {
                    showStats = false;
                    switch (event.key.scancode)
                    {
                    case sf::Keyboard::Scan::R:
                        // set all shapes white again
                        for (int i = 0; i < MAX_ARRAY_SIZE; i++)
                            sort.shapes[i].rect.setFillColor(sf::Color::White);
                        showStats = false;
                        sort.shuffle();
                        break;

                    case sf::Keyboard::Scan::Num1: // bubble sort selected
                        title_text.setString("Bubble Sort");
                        sort.chosenAlgorithm = bubble_sort;
                        break;

                    case sf::Keyboard::Scan::Num2:
                        title_text.setString("Merge Sort");
                        sort.chosenAlgorithm = merge_sort;
                        break;
                    
                    case sf::Keyboard::Scan::Num3:
                        title_text.setString("Selection Sort");
                        sort.chosenAlgorithm = selection_sort;
                        break;
                    
                    case sf::Keyboard::Scan::Num4:
                        title_text.setString("Insertion Sort");
                        sort.chosenAlgorithm = insertion_sort;
                        break;

                    case sf::Keyboard::Scan::Space:
                        sort.numArrayAccess = 0;
                        sort.numSwaps = 0;
                        showStats = true;
                        sortThread = std::thread(&Sort::doSort, std::ref(sort)); // spawn the sorting thread
                        break;

                    default:
                        break;
                    }
                }
                // commands usable while sorting
                else if (event.key.scancode == sf::Keyboard::Scan::K)
                {
                    sort.killThread = true;
                }
                break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // get bounds of repo_Text
                    sf::FloatRect bounds = repo_text.getGlobalBounds();
                    if (event.mouseButton.x > bounds.left && event.mouseButton.y < (bounds.top + bounds.height) )
                    {
                        // open url
                        std::cout << "open url\n";
                    }
                }
                break;

            default:
                break;
            }
        }
        
        doDraw();

        if (sort.sortDone || sort.killThread)
        {
            sort.sortDone = false;
            sortThread.join();
            sort.killThread = false;
        }
    }
}

void Renderer::doDraw()
{
    window.clear(sf::Color::Black); // clear the screen

    // update string with numswaps and numarray acces
    if (showStats)
    {
        // get string first
        std::string text = cleanTitle();
        // format the stat string
        std::string stat_str = string_format(" - Swaps: %d   Array Access: %d", sort.numSwaps, sort.numArrayAccess);
        title_text.setString(text + stat_str);
    }

    // render title
    window.draw(title_text);
    window.draw(repo_text);

    // update rect positions based on sort algorithm
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        window.draw(sort.shapes[i].rect);

    window.display(); // write to the screen
}

void Renderer::titleTextInit()
{
    // init left side text
    title_text.setFont(font);
    title_text.setString("Bubble Sort");
    title_text.setCharacterSize(TITLE_HEIGHT - 5);
    title_text.setFillColor(sf::Color::White);
    title_text.setPosition(sf::Vector2f(0, 0));

    // init right side text
    repo_text.setFont(font);
    repo_text.setString("https://github.com/FatRat60/AlgoVis");
    repo_text.setCharacterSize(TITLE_HEIGHT - 5);
    repo_text.setFillColor(sf::Color::White);
    float width = repo_text.getGlobalBounds().width; // get bounds of text
    unsigned int screen_x = window.getSize().x; // get x of window
    repo_text.setPosition(sf::Vector2f(screen_x - width, 0));
}

std::string Renderer::cleanTitle()
{
    std::string dirtyTitle = title_text.getString();
    // iterate till - and discard anything after that
    size_t n = 0;
    auto it = dirtyTitle.begin();
    while (*it != '-' && it < dirtyTitle.end())
    {
        it++;
        n++;
    }
    
    return dirtyTitle.substr(0, n - (it != dirtyTitle.end())); // subtract n by 1 only if end not reached
}

template<typename ... Args>
std::string Renderer::string_format(const std::string& format, Args ... args)
{
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
    if ( size <= 0) return "";
    std::unique_ptr<char[]> buf( new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1);
}
