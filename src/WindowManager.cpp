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

sf::RenderWindow& WindowManager::getWindowAdress(){
    return *window;
}

void WindowManager::draw(){
    window->clear();

    for (int i = 100; i > 0; i--){
        shape.setFillColor(sf::Color(255-i, 255-2*i, 255-i/2));
        shape.setOrigin(i-100, i-100);
        shape.setRadius(i);
        window->draw(shape);
    }
    window->display();
}
