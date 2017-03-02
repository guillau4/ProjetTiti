#include "EventManager.h"

EventManager::EventManager(WindowManager& wM)
: winMan(&wM)
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
                click(event);
                break;

            case sf::Event::KeyPressed :
                keyboard(event);
                break;



            default :
                break;
        }
    }
}

void EventManager::click(sf::Event event){
    switch (event.mouseButton.button){
        case sf::Mouse::Right:
            switch (winMan->typeClick()){
            // Asks windowManager what we just clicked on

                case 1 :
                    winMan->changeBackground(1);
                    break;

                case 2 :
                    winMan->changeBackground(2);
                    break;

                default :
                    winMan->setMode3();
                    break;
            }
            break;

        default :
            switch (winMan->typeClick()){
            // Asks windowManager what we just clicked on

                case 1 :
                    winMan->changeBackground(1);
                    break;

                case 2 :
                    winMan->changeBackground(2);
                    break;

                default :
                    winMan->setMode3();
                    break;
            }
            break;
    }
}


void EventManager::keyboard(sf::Event event){

    switch (event.key.code){

        case sf::Keyboard::Escape :
            window->close();
            break;

        default :
            // ignores other keys
            break;
    }
}
