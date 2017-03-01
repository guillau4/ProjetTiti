#include "EventManager.h"

EventManager::EventManager(WindowManager& wM)
: winMan(wM)
, window(&(wM.getWindowAddress()))
{

}

EventManager::~EventManager()
{
    //dtor
}

void EventManager::checkEvent(){
    while (window->pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed :
                window->close();
                break;

            case sf::Event::MouseButtonPressed :
                clic(event);
                break;



            default :
                break;
        }
    }
}

void EventManager::clic(sf::Event event){
    switch (event.mouseButton.button){
        case sf::Mouse::Right:
            switch (winMan.typeClic(event.mouseButton.x, event.mouseButton.y)){
                // Ask windowManager what we just clicked on

                case 1 :
                    break;

                default :
                    break;
            }
            break;

        default :
            // ignores other kind of clicks
            break;
    }
}
