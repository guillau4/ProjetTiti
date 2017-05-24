#include "../include/AudioFile.h"

AudioFile::AudioFile()
{
    //ctor
}

AudioFile::AudioFile(std::string name) :
name        (name)          ,
extension   ("")            ,
pathIn      ("original\\")  ,
pathOut     ("created\\")   {

    open();
}

AudioFile::AudioFile(std::string name,
                     std::string extension,
                     std::string pathIn,
                     std::string pathOut) :

name        (name)      ,
extension   (extension) ,
pathIn      (pathIn)    ,
pathOut     (pathOut)   {

    open();

}

AudioFile::~AudioFile()
{
    // Should make sure the files are closed
}


int AudioFile::open() {

    // Step 1 : Should test if the original is missing

    // Step 2 : Open the original
    openIn();

    return 0;

}


int AudioFile::openIn() {
    fileIn.open(pathIn + name + extension, std::ios::binary);

    return 0;
}


int AudioFile::openOut() {
    fileOut.open(pathOut + name + extension, std::ios::binary);

    return 0;
}

int AudioFile::openOut(int n) {
    std::string name_;

    std::stringstream sstm;
    sstm << pathOut << name << "_" << n << extension;
    name_ = sstm.str();

    fileOut.open(name_, std::ios::binary);

    return 0;
}


int AudioFile::findNameAndOpenOut() {

    std::string name_;

    std::cout << "\tLooking for an unused output name :" << std::endl;
    std::cout << std::endl;

    // Step 3 : Creating a new file in the "created" folder
    name_ = pathOut + name + extension;
    if (!exists_test(name_)) {
        // Step 3.1 : If the file does not exit yet
        openOut();

    } else {
        // Step 3.2 : Else we  add "_2" or "_3" etc to make it unique
        int i = 1;

        do {
            i++;
            std::stringstream sstm;
            sstm << pathOut << name << "_" << i << extension;
            name_ = sstm.str();

            if (i > 1000) {
                // If i reaches 1000 there is most likely bug
                // We should raise an error
                break;
            }
        } while (exists_test(name_));
        openOut(i);
    }

    std::cout << std::endl;
    std::cout << "  Name found : " << name_ << std::endl;
    std::cout << std::endl;
    std::cout << " =================================================="<< std::endl;

    return 0;
}


int AudioFile::close() {
    fileIn.close();
    fileOut.close();

    return 0;
}


int AudioFile::save() {

    findNameAndOpenOut();

    return 0;
}


int AudioFile::delay(float seconds) {
    std::cout << "  Applying delay ... ";

    audioOut = Effect::delay(seconds, audioOut);
    std::cout << "Done" << std::endl;

    return 0;
}
int AudioFile::gain(double factor) {
    std::cout << "  Applying gain ... ";

    audioOut = Effect::gain(factor, audioOut);
    std::cout << "Done" << std::endl;

    return 0;
}

int AudioFile::clone() {
    std::cout << "  Cloning audioIn into audioOut ... ";

//    int dim1 = audioIn.NbrCanaux,
//        dim2 = audioIn.DataSize / audioIn.BytePerBloc;

    audioOut = audioIn;
//    audioOut.Data = deepCopy(audioIn.Data, dim1, dim2);

    assert(audioOut.Data.size() == audioIn.Data.size());

    std::cout << "Done" << std::endl;

    return 0;
}






// ======================================================================
// tools used to read files

// reads *length* bytes from *file* and transform it as a string
std::string AudioFile::toString(int length) {
    char * buffer = new char [length];

    fileIn.read (buffer, length);

    std::string s(buffer, length);

    return s;
}

// *length* bytes from *s* transformed into a char*
char * AudioFile::toChar(std::string s, unsigned int length) {
    char * c = new char [length];

    for (unsigned int i = 0; i < length; i += 1) {
        if (i < s.length()) {
            c[i] = s[i];
        } else {
            c[i] = 0;
        }
    }
    return c;
}

// *length* bytes from *l* transformed into a char*
char * AudioFile::toChar(unsigned long l, unsigned int length) {
    char * c = new char [length];

    for (unsigned int i = 0; i < length; i += 1) {
        c[i] = (char) (l % 256);
        l /= 256;

    }
    return c;
}


// reads *length* bytes from *file* and transform it as an unsigned long ("little endian" form)
unsigned long AudioFile::toLong(int length) {

    if (length < 1 || length > 4) {
        return -1;
    }

    char * buffer = new char [length];
    unsigned long returnLong = 0;

    fileIn.read (buffer, length);

    for (int i = 0; i < length; i += 1) {
        int power = 1;
        for (int j = 0; j < i; j += 1) {
            power *= 256;
        }
        returnLong += (unsigned char) buffer[i] * power;
    }

    return returnLong;
}


/*
int ** AudioFile::deepCopy(int ** c, int dim1, int dim2) {
    int ** d = new int * [dim1];

    for (int i = 0; i < dim1; i += 1) {
        d[i] = new int [dim2];

        for (int j = 0; j < dim2; j += 1) {
            d[i][j] = c[i][j];
        }
    }

    return d;
}



unsigned char ** AudioFile::deepCopy(unsigned char ** c, int dim1, int dim2) {
    unsigned char ** d = new unsigned char * [dim1];

    for (int i = 0; i < dim1; i += 1) {
        d[i] = new unsigned char [dim2];

        for (int j = 0; j < dim2; j += 1) {
            d[i][j] = c[i][j];
        }
    }

    return d;
}




unsigned char ** AudioFile::intToUCharArray(int ** c, int dim1, int dim2) {
    unsigned char ** d = new unsigned char * [dim1];

    for (int i = 0; i < dim1; i += 1) {
        d[i] = new unsigned char [dim2];

        for (int j = 0; j < dim2; j += 1) {
            d[i][j] = (unsigned char) (c[i][j] / 256 + 128);
        }
    }

    return d;
}



int ** AudioFile::uCharToIntArray(unsigned char ** c, int dim1, int dim2) {
    int ** d = new int * [dim1];

    for (int i = 0; i < dim1; i += 1) {
        d[i] = new int [dim2];

        for (int j = 0; j < dim2; j += 1) {
            d[i][j] = (c[i][j] - 128) * 256;
        }
    }

    return d;
}
*/


std::vector<std::vector<unsigned char>> AudioFile::intToUCharArray(std::vector<std::vector<int>> c) {

    std::vector<std::vector<unsigned char>> d;

    for (unsigned int i = 0; i < c.size(); i += 1) {

        std::vector<unsigned char> di;
        for (unsigned int j = 0; j < c[i].size(); j += 1) {
            di.push_back((unsigned char) (c[i][j] / 256 + 128));
        }
        d.push_back(di);
    }

    return d;
}



std::vector<std::vector<int>> AudioFile::uCharToIntArray(std::vector<std::vector<unsigned char>> c) {

    std::vector<std::vector<int>> d;

    for (unsigned int i = 0; i < c.size(); i += 1) {

        std::vector<int> di;
        for (unsigned int j = 0; j < c[i].size(); j += 1) {
            di.push_back((c[i][j] - 128) * 256);
        }
        d.push_back(di);
    }

    return d;
}




// Test if file exists
// "Inline" means the compiler will write it directly in the code
// Not necessary, but we do not use this function a lot anyway
inline bool AudioFile::exists_test (std::string name) {
    std::cout << "  Testing name " << name << std::endl;
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}




