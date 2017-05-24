#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include "Formats.h"
#include "Effect.h"


/*

    Objet lié à une fichier audio pécis

    Divisé en deux sous classes selon
    le mode d'ouverture (lecture ou ecriture)

    Gère le type d'encodage

*/




class AudioFile
{
    public:
        AudioFile(std::string name);

        AudioFile(std::string name,
                  std::string extension,
                  std::string pathIn,
                  std::string pathOut);

        virtual ~AudioFile();

        virtual int save(){return 0;};
        AUDIO * getAUDIOadd() {return &my_AUDIO;};
        std::string getName() {return name;};
        std::string getFileName() {return name + extension;};

    protected:
        // Opening and closing files
        int open();
        int openIn();
        int openOut();
        int openOut(int n);
        int findNameAndOpenOut();
        virtual void createFile(){};

        // Reading and writing in files
        std::string toString(int length);
        unsigned long toLong(int length);
        char * toChar(std::string s, unsigned int length);
        char * toChar(unsigned long l, unsigned int length);

        // Cloning char **
        /*
        int ** deepCopy(int ** c, int dim1, int dim2);
        unsigned char ** deepCopy(unsigned char ** c, int dim1, int dim2);
        int ** uCharToIntArray(unsigned char ** c, int dim1, int dim2);
        unsigned char ** intToUCharArray(int ** c, int dim1, int dim2);

        std::vector <std::vector <int> > uCharToIntArray(std::vector <std::vector <unsigned char> > c);
        std::vector <std::vector <unsigned char> > intToUCharArray(std::vector <std::vector <int> > c);
        */


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
        AUDIO my_AUDIO;


    private:
};

#endif // AUDIOFILE_H
