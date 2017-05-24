#include <string>
#include <iostream>

#include "include/ConsoleStream.h"
#include "include/FileManager.h"
#include "include/Effect.h"


int main()
{


    // Test audio manipulation

    FileManager file_manager;

    std::string file1 = "canary.wav",
                file2 = "ball.wav",
                file3 = "saw.wav",
                file = file3;

    // Open the files
    file_manager.open(file);

    // Apply some effects
//    Effect::gain(file_manager.getAUDIOadd(file), 0.01);
//    Effect::delay(file_manager.getAUDIOadd(file), 1.5);
//    Effect::gain(file_manager.getAUDIOadd(file), 100);

    Effect::add1sec(file_manager.getAUDIOadd(file));

    // Export it
    file_manager.save(file);


    // End test



    return 0;
}
