#include "../include/FileManager.h"



FileManager::FileManager()
{
    //ctor
}

FileManager::~FileManager()
{
    //dtor
}

int FileManager::open(std::string fileName) {

    std::string name;
    std::string extension;

    // Step 0 : Should check if the original exists

    // Step 1 : Get the type of the file
    // reading the extension (for now only wav)
    name = fileName.substr(0, fileName.find('.'));
    extension = fileName.substr(fileName.find('.'));

    std::cout << " =================================================="<< std::endl;
    std::cout << "\tOpening the following file : " << std::endl;;
    std::cout << std::endl;

    std::cout << "            Name : " << name << std::endl;
    std::cout << "       Extension : " << extension << std::endl;
    std::cout << std::endl;

    // Step 2 : Creating the object
    if (extension == ".wav") {
        audioList.push_back(new AudioFileWAV(name));

    } else {
        audioList.push_back(new AudioFile(name));

    }

    return 0;
}


/*

    Depth is used in case a file is opened several times

    The function will browse the vector and delete the
    file once it has seen it depth time (delete the depth-th name entry)

*/

int FileManager::close(std::string fileName, unsigned int depth) {

    // Step 1 : find the file
    int index = getIndex(fileName, depth);

    // Step 1.ERROR : file not found
    if (index == -1) {
        return -1;
    }

    // Step 2 : close the files
    audioList[index]->close();

    // Step 3 : delete the pair from the list
    audioList.erase(audioList.begin() + index);

    // Step 4 : return 0 or an error flag
    return 0;
}



int FileManager::getIndex(std::string fileName, unsigned int depth) {
    int found,
        index;

    // Step 0 : initialize an int to match depth
    found = -depth;

    // Step 1 : find the file
    index = -1;
    for (unsigned int i = 0; i < audioList.size(); i++) {
//        if (audioList[i] != null) {
            if (audioList[i]->getFileName() == fileName) {
                // If we reached the right depth we can stop
                if (found == 0) {
                    index = i;
                    break;

                } else {
                    found += 1;
                }
            }
//        }
    }

    return index;
}




/*

    Depth is used in case a file is opened several times

    The function will browse the vector and copy AudioIn into audioOut
    once it has seen it depth time (save the depth-th name entry)

*/

int FileManager::clone(std::string fileName, unsigned int depth) {


    // Step 1 : find the file
    int index = getIndex(fileName, depth);

    // Step 1.ERROR : file not found
    if (index == -1) {
        return -1;
    }

    // Step 2 : clone the file
    audioList[index]->clone();

    // Step 3 : return 0 or an error flag
    return 0;
}



int FileManager::delay(float seconds, std::string fileName, unsigned int depth) {


    // Step 1 : find the file
    int index = getIndex(fileName, depth);

    // Step 1.ERROR : file not found
    if (index == -1) {
        return -1;
    }

    // Step 2 : apply effect the file
    audioList[index]->delay(seconds);

    // Step 3 : return 0 or an error flag
    return 0;
}





/*

    Depth is used in case a file is opened several times

    The function will browse the vector and save the audio created in the
    found file once it has seen it depth time (save the depth-th name entry)

*/

int FileManager::save(std::string fileName, unsigned int depth) {

    // Step 1 : find the file
    int index = getIndex(fileName, depth);

    // Step 1.ERROR : Did not find the file
    if (index == -1) {
        return -1;
    }

    // Step 2 : save the file
    audioList[index]->save();

    // Step 3 : return 0 or an error flag
    return 0;
}
