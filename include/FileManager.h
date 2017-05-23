#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "AudioFileWAV.h"
#include "AudioFile.h"

#include <vector>



/*

    Contient la liste des fichiers ouverts (audio_list)
    Gère l'ouverture et la fermeture de ces fichiers

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
        int close(std::string fileName, unsigned int depth = 0);
        int save(std::string fileName, unsigned int depth = 0);

        int clone(std::string fileName, unsigned int depth = 0);
        int delay(float seconds, std::string fileName, unsigned int depth = 0);

        int getIndex(std::string fileName, unsigned int depth = 0);
        int getSize() {return audioList.size();};

    protected:

    private:
        std::vector<AudioFile*> audioList;


};

#endif // FILEMANAGER_H
