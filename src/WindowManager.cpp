#include "WindowManager.h"

WindowManager::WindowManager(sf::RenderWindow &w)
: window(&w)
, red(0)
, green(0)
, blue(0)
, alpha(255)
, mode3(0)
{
    shape.setFillColor(sf::Color::Cyan);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(0);
}

WindowManager::~WindowManager()
{
    //dtor
}

sf::RenderWindow& WindowManager::getWindowAddress(){
    return *window;
}

void WindowManager::draw(){

    // Clearing the screen and setting a background
    window->clear(sf::Color(red, green, blue, alpha));

    if (mode3){
        sf::Vector2f v = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        window->clear(sf::Color(v.x*255.0/1000.0, v.y*255.0/800.0, 127+125*sin(clock.getElapsedTime().asSeconds())));
    }

    // Drawing buttons
    for(unsigned int i = 0; i < allButtons.size(); i++){
        window->draw(allButtons[i].rect);
    }


    // Displaying all on the screen
    window->display();
}

int WindowManager::typeClick(){

    for (int i = 0; i < allButtons.size(); i++){
        widget w = allButtons[i];
        if (w.rect.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
         {
             return w.type;
         }
    }
    return -1;
}


void WindowManager::addButton(int x, int y, int w, int h, int t){
    widget b;
    b.rect.setPosition(x, y);
    b.rect.setSize(sf::Vector2f(w, h));
    b.type = t;

    if (t == 1) {
        b.rect.setFillColor(sf::Color(255, 0, 0, 255));
    } else if (t == 2) {
        b.rect.setFillColor(sf::Color(0, 125, 255, 255));
    }

    addButton(b);
}

void WindowManager::addButton(widget w){
    allButtons.push_back(w);
}

void WindowManager::changeBackground(int type){
    int z = 25;
    if (type == 1){
        red += z;
        green -= z;
        blue -= z;
    } else if (type == 2) {
        red -= z;

        if (green > 125+z)
            green -= z;
        else green += z;

        blue += z;
    }
    if (red > 255) red = 255;
    if (green > 255) green = 255;
    if (blue > 255) blue = 255;
    if (red < 0) red = 0;
    if (green < 0) green = 0;
    if (blue < 0) blue = 0;

}

void WindowManager::setMode3(){
    mode3++;
    mode3 %= 2;

    for(int i = 0; i < allButtons.size(); i++){
        sf::Color c = allButtons[i].rect.getFillColor();
        if(c.a == 255)
            allButtons[i].rect.setFillColor(sf::Color(c.r, c.g, c.b, 125));
        else allButtons[i].rect.setFillColor(sf::Color(c.r, c.g, c.b, 255));
    }

}
