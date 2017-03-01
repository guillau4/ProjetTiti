#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SFML/Graphics.hpp>

class WindowManager
{
    public:
        WindowManager(sf::RenderWindow &w);
        virtual ~WindowManager();
        void draw();
        sf::RenderWindow& getWindowAdress();

    protected:

    private:
        sf::RenderWindow *window;
        sf::CircleShape shape;
};

#endif // WINDOWMANAGER_H
