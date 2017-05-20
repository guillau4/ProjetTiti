#include "FileManager.h"

int main()
{


    // Test audio manipulation

    FileManager file_manager;

    std::string file1 = "canary.wav",
                file2 = "ball.wav",
                file3 = "808 OH.wav",
                file = file3;

    file_manager.open(file);
    file_manager.clone(file);

    // Apply effects

    file_manager.save(file);
    file_manager.close(file);

    if (file_manager.getSize() == 0) {
        std::cout << "  Vector cleared properly" << std::endl;

    } else {
        std::cout << "  WARNING : Vector not cleared properly !" << std::endl;

    }
    // End test



    return 0;
}
