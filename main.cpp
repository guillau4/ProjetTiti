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
                file = file2;

    // Open the files
    file_manager.open(file);

    // Apply some effects
    Effect::echo(file_manager.getAUDIOadd(file), 0.1, 0.7);

    // Export it
    file_manager.save(file);


    // End test



    return 0;
}
