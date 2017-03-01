#include "EventManager.h"

EventManager::EventManager(sf::RenderWindow &w)
: window(&w)
{

}

EventManager::~EventManager()
{
    //dtor
}

void EventManager::checkEvent(){
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch(event.type){
            case(sf::Event::Closed) :
                window->close();
            break;

            case(sf::Event::MouseButtonPressed) :
                switch(event.mouseButton.button){
                    case(sf::Mouse::Right) :
                        //
                    break;

                    default:
                    break;
                }
            break;

            default :
            break;
        }
    }
}
