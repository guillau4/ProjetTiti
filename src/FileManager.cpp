#include "FileManager.h"



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
        audio_list.push_back(new AudioFileWAV(name));

    } else {
        audio_list.push_back(new AudioFile(name));

    }

    return 0;
}


int FileManager::close(std::string fileName) {
    return close(fileName, 0);

}

/*

    Depth is used in case a file is opened several times

    The function will browse the vector and delete the
    file once it has seen it depth time (delete the depth-th name entry)

*/

int FileManager::close(std::string fileName, unsigned int depth) {

    // Step 1 : find the file
    int index_file = getIndex(fileName, depth);

    // Step 1.ERROR : file not found
    if (index_file == -1) {
        return -1;
    }

    // Step 2 : close the files
    audio_list[index_file]->close();

    // Step 3 : delete the pair from the list
    audio_list.erase(audio_list.begin() + index_file);

    // Step 4 : return 0 or an error flag
    return 0;
}



int FileManager::getIndex(std::string fileName, unsigned int depth) {
    int found,
        index_file;

    // Step 0 : initialize an int to match depth
    found = -depth;

    // Step 1 : find the file
    index_file = -1;
    for (unsigned int i = 0; i < audio_list.size(); i++) {
//        if (audio_list[i] != null) {
            if (audio_list[i]->getFileName() == fileName) {
                // If we reached the right depth we can stop
                if (found == 0) {
                    index_file = i;
                    break;

                } else {
                    found += 1;
                }
            }
//        }
    }

    return index_file;
}




int FileManager::clone(std::string fileName) {
    return clone(fileName, 0);

}

/*

    Depth is used in case a file is opened several times

    The function will browse the vector and copy AudioIn into audioOut
    once it has seen it depth time (save the depth-th name entry)

*/

int FileManager::clone(std::string fileName, unsigned int depth) {


    // Step 1 : find the file
    int index_file = getIndex(fileName, depth);

    // Step 1.ERROR : file not found
    if (index_file == -1) {
        return -1;
    }

    // Step 2 : clone the file
    audio_list[index_file]->clone();

    // Step 3 : return 0 or an error flag
    return 0;
}




int FileManager::delay(float seconds, std::string fileName) {
    return delay(seconds, fileName, 0);

}
int FileManager::delay(float seconds, std::string fileName, unsigned int depth) {


    // Step 1 : find the file
    int index_file = getIndex(fileName, depth);

    // Step 1.ERROR : file not found
    if (index_file == -1) {
        return -1;
    }

    // Step 2 : apply effect the file
    audio_list[index_file]->delay(seconds);

    // Step 3 : return 0 or an error flag
    return 0;
}





/*

    Depth is used in case a file is opened several times

    The function will browse the vector and save the audio created in the
    found file once it has seen it depth time (save the depth-th name entry)

*/
int FileManager::save(std::string fileName) {
    return save(fileName, 0);

}
int FileManager::save(std::string fileName, unsigned int depth) {

    // Step 1 : find the file
    int index_file = getIndex(fileName, depth);

    // Step 1.ERROR : Did not find the file
    if (index_file == -1) {
        return -1;
    }

    // Step 2 : save the file
    audio_list[index_file]->save();

    // Step 3 : return 0 or an error flag
    return 0;
}
