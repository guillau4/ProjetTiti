#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>


/*

    Objet lié à une fichier audio pécis

    Divisé en deux sous classes selon
    le mode d'ouverture (lecture ou ecriture)

    Gère le type d'encodage

*/


class AudioFile
{
    public:
        AudioFile();
        AudioFile(std::string name);

        AudioFile(std::string name,
                  std::string extension,
                  std::string pathIn,
                  std::string pathOut);

        virtual ~AudioFile();

        int close();
        std::string getName() {return name;};
        std::string getFileName() {return name + extension;};

    protected:
        // Opening and closing files
        int open();
        int openIn(std::string name);
        int openOut(std::string name);
        int openOut(std::string name, int n);

        // Reading and writing in files
        std::string toString(int length);
        unsigned long toLong(int length);
        char * toChar(std::string s, unsigned int length);
        char * toChar(unsigned long l, unsigned int length);

        // Test a file name
        inline bool exists_test(std::string name);

        // The files
        std::ifstream fileIn;
        std::ofstream fileOut;

        // Description of the files
        std::string name;
        std::string extension;
        std::string pathIn;
        std::string pathOut;



    private:
};

#endif // AUDIOFILE_H
