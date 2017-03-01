#include "WindowManager.h"

WindowManager::WindowManager(sf::RenderWindow &w)
: window(&w)
, shape(sf::CircleShape(100.f))
{
    shape.setFillColor(sf::Color::Cyan);
}

WindowManager::~WindowManager()
{
    //dtor
}

sf::RenderWindow& WindowManager::getWindowAddress(){
    return *window;
}

void WindowManager::draw(){
    window->clear();
    double theta;
    double r;
    for (int i = 1000; i > 0; i--){
        shape.setFillColor(sf::Color(255-i, 255-2*i, 255-i/2));
        r = 30-i/5000.0;
        theta = i/1.0;
        shape.setOrigin(i-100 + r*cos(theta), i-100 + r*sin(theta));
        shape.setRadius(i);
        window->draw(shape);

        shape.setFillColor(sf::Color(i, i/2, i*2));
        shape.setOrigin(i-100 - r*cos(theta), i-100 - r*sin(theta));
        window->draw(shape);
    }
    window->display();
}

int WindowManager::typeClic(int x, int y){


    return 0;
}


void WindowManager::addButton(int x, int y, int w, int h, int t){
    widget b;
    b.x = x;
    b.y = y;
    b.xlenght= w;
    b.ylenght = h;
    b.type = t;
    addButton(b);
}

void WindowManager::addButton(widget w){
    allButtons.push_back(w);
}
