#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SFML/Graphics.hpp>
#include "WindowManager.h"

class EventManager
{
    public:
        EventManager(WindowManager &wM);
        virtual ~EventManager();
        void checkEvent();
        void clic(sf::Event event);

    protected:

    private:
        WindowManager winMan;
        sf::RenderWindow* window;
        sf::Event event;
};

#endif // EVENTMANAGER_H
