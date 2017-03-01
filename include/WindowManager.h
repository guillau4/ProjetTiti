#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

typedef struct{
    int x;
    int y;
    int xlenght;
    int ylenght;
    int type;
} widget;

class WindowManager
{
    public:
        WindowManager(sf::RenderWindow &w);
        virtual ~WindowManager();
        sf::RenderWindow& getWindowAddress();
        void draw();
        int typeClic(int x, int y);
        void addButton(int x, int y, int w, int h, int t);
        void addButton(widget w);

    protected:

    private:
        sf::RenderWindow *window;
        sf::CircleShape shape;
        std::vector<widget> allButtons;
};

#endif // WINDOWMANAGER_H
