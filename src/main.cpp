#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sort.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // TODO: Create sorting thread
    Renderer renderer = Renderer();
    renderer.EventLoop();
    
    return 0;
}
