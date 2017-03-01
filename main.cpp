#include <SFML/Graphics.hpp>

#include "EventManager.h"
#include "WindowManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    WindowManager winMan(window);
    EventManager evMan(window);

    while (window.isOpen())
    {
        evMan.checkEvent();

        winMan.draw();
    }

    return 0;
}
