#include <SFML/Graphics.hpp>

#include "FileManager.h"

int main()
{


    // Test audio manipulation

    FileManager file_manager;

    file_manager.open("canary.wav");
    file_manager.close("canary.wav");

    if (file_manager.getSize() == 0) {
        std::cout << "  Vector cleared properly" << std::endl;
    } else {
        std::cout << "  WARNING : Vector not cleared properly !" << std::endl;
    }
    // End test



    return 0;
}
