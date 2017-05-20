#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <iostream>
#include <string>
#include <vector>
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


typedef struct {

    std::string FileTypeBlocID;
    unsigned long FileSize;
    std::string FileFormatID;

    std::string FormatBlocID;
    unsigned long BlocSize;

    unsigned long AudioFormat;
    unsigned long NbrCanaux;
    unsigned long Frequence;
    unsigned long BytePerSec;
    unsigned long BytePerBloc;
    unsigned long BitsPerSample;

    std::string DataBlocID;
    unsigned long DataSize;

    char ** Data;

} AUDIO;



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

        virtual int clone();
        virtual int save();
        int close();
        std::string getName() {return name;};
        std::string getFileName() {return name + extension;};

    protected:
        // Opening and closing files
        int open();
        int openIn();
        int openOut();
        int openOut(int n);
        int findNameAndOpenOut();

        // Reading and writing in files
        std::string toString(int length);
        unsigned long toLong(int length);
        char * toChar(std::string s, unsigned int length);
        char * toChar(unsigned long l, unsigned int length);

        // Cloning char **
        char ** deepCopy(char ** c, int dim1, int dim2);

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
        AUDIO audioIn;
        AUDIO audioOut;



    private:
};

#endif // AUDIOFILE_H
