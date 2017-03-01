#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SFML/Graphics.hpp>


class EventManager
{
    public:
        EventManager(sf::RenderWindow &w);
        virtual ~EventManager();
        void checkEvent();

    protected:

    private:
        sf::RenderWindow* window;
};

#endif // EVENTMANAGER_H
