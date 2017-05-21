#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "AudioFileWAV.h"
#include "AudioFile.h"

#include <vector>



/*

    Contient la liste des fichiers ouverts (audio_list)
    G�re l'ouverture et la fermeture de ces fichiers

    Cette liste est un vecteur d'objets "AudioFile", objet
    qui contient un fichier en mode lecture (original) et
    un fichier en mode ecriture (sur lequel on applique des effets)

*/


class FileManager
{
    public:
        FileManager();
        virtual ~FileManager();

        int open(std::string fileName);
        int close(std::string fileName);
        int close(std::string fileName, unsigned int depth);

        int getIndex(std::string fileName, unsigned int depth);

        int clone(std::string fileName);
        int clone(std::string fileName, unsigned int depth);

        int delay(float seconds, std::string fileName);
        int delay(float seconds, std::string fileName, unsigned int depth);

        int save(std::string fileName);
        int save(std::string fileName, unsigned int depth);

        int getSize() {return audio_list.size();};

    protected:

    private:
        std::vector<AudioFile*> audio_list;


};

#endif // FILEMANAGER_H
