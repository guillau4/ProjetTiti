#include <SFML/Graphics.hpp>

#include "EventManager.h"
#include "WindowManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");

    WindowManager winMan(window);
    EventManager evMan(winMan);

    winMan.addButton(350, 100, 300, 200, 1);
    winMan.addButton(350, 500, 300, 200, 2);

    while (window.isOpen())
    {
        evMan.checkEvent();
        winMan.draw();
    }

    return 0;
}
