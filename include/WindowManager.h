#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

typedef struct{
    sf::RectangleShape rect;
    int type;
} widget;

class WindowManager
{
    public:
        WindowManager(sf::RenderWindow &w);
        virtual ~WindowManager();
        sf::RenderWindow& getWindowAddress();
        void draw();
        int typeClick();
        void addButton(int x, int y, int w, int h, int t);
        void addButton(widget w);
        void changeBackground(int type);
        void setMode3();

    protected:

    private:
        sf::Clock clock;
        sf::RenderWindow *window;
        sf::RectangleShape shape;
        std::vector<widget> allButtons;
        int red, green, blue, alpha, mode3;
};

#endif // WINDOWMANAGER_H
