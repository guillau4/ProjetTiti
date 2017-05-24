#include "../include/AudioFileWAV.h"


AudioFileWAV::AudioFileWAV(std::string name) :
AudioFile(name, ".wav", "wav\\", "created\\"){

    readWAV();
    assert(my_WAV.Data.size() == my_WAV.NbrCanaux);

    updateAUDIO();
    assert(my_AUDIO.Data.size() == my_WAV.Data.size());

}



AudioFileWAV::~AudioFileWAV()
{
    delete[] my_WAV.ExtraParamLong;
    delete[] my_WAV.ExtraParamString;
}




void AudioFileWAV::readWAV() {

    std::cout << " =================================================="<< std::endl;
    std::cout << "\tReading inFile header : "<< std::endl;
    std::cout << std::endl;
    readHeaderWAV();
// my_WAV updated

    std::cout << "\tReading inFile data : "<< std::endl;
    std::cout << std::endl;
    getDataWAV();
// *my_WAV.DataSize* bytes of data

}





void AudioFileWAV::readHeaderWAV(){


    fileIn.seekg (0, fileIn.beg);


// ====================================================
//    [Bloc de déclaration d'un fichier au format WAVE]
// ====================================================

    my_WAV.FileTypeBlocID = toString(4);
    std::cout << "  FileTypeBlocID : " << my_WAV.FileTypeBlocID << std::endl;
//  (4 octets) : Constante «RIFF»  (0x52,0x49,0x46,0x46)

    my_WAV.FileSize = toLong(4);
    std::cout << "        FileSize : " << my_WAV.FileSize << std::endl;
//  (4 octets) : Taille du fichier moins 8 octets

    my_WAV.FileFormatID = toString(4);
    std::cout << "    FileFormatID : " << my_WAV.FileFormatID << std::endl;
//  (4 octets) : Format = «WAVE»  (0x57,0x41,0x56,0x45)

// ====================================================
//    [Bloc décrivant le format audio]
// ====================================================

    std::cout << std::endl;

    my_WAV.FormatBlocID = toString(4);
    std::cout << "    FormatBlocID : " << my_WAV.FormatBlocID << std::endl;
//  (4 octets) : Identifiant «fmt »  (0x66,0x6D, 0x74,0x20)

    my_WAV.BlocSize = toLong(4);
    std::cout << "        BlocSize : " << my_WAV.BlocSize << std::endl;
//  (4 octets) : Nombre d'octets du bloc - 16  (0x10)

    my_WAV.AudioFormat = toLong(2);
    std::cout << "     AudioFormat : " << my_WAV.AudioFormat << std::endl;
//  (2 octets) : Format du stockage dans le fichier (1: PCM, ...)

    my_WAV.NbrCanaux = toLong(2);
    std::cout << "       NbrCanaux : " << my_WAV.NbrCanaux << std::endl;
//  (2 octets) : Nombre de canaux (de 1 à 6, cf. ci-dessous)

    my_WAV.Frequence = toLong(4);
    std::cout << "       Frequence : " << my_WAV.Frequence << std::endl;
//  (4 octets) : Fréquence d'échantillonnage (en hertz) [Valeurs standardisées : 11025, 22050, 44100 et éventuellement 48000 et 96000]

    my_WAV.BytePerSec = toLong(4);
    std::cout << "      BytePerSec : " << my_WAV.BytePerSec << std::endl;
//  (4 octets) : Nombre d'octets à lire par seconde (c.-à-d., Frequence * BytePerBloc).

    my_WAV.BytePerBloc = toLong(2);
    std::cout << "     BytePerBloc : " << my_WAV.BytePerBloc << std::endl;
//  (2 octets) : Nombre d'octets par bloc d'échantillonnage (c.-à-d., tous canaux confondus : NbrCanaux * BitsPerSample/8).

    my_WAV.BitsPerSample = toLong(2);
    std::cout << "   BitsPerSample : " << my_WAV.BitsPerSample << std::endl;
//  (2 octets) : Nombre de bits utilisés pour le codage de chaque échantillon (8, 16, 24)

// ====================================================
//    [Bloc optionnel]
// ====================================================
    int surplus;

    if (my_WAV.AudioFormat != 1) {
        my_WAV.ExtraParamSize = toLong(2);
        std::cout << "  ExtraParamSize : " << my_WAV.ExtraParamSize << std::endl;
//  (2 octets) : Utilisé lorsque le format de stockage de data n'est pas en PCM linéaire

        my_WAV.ExtraParamString = new std::string [my_WAV.ExtraParamSize / 4];
        my_WAV.ExtraParamLong = new unsigned long [my_WAV.ExtraParamSize / 4];

        for (unsigned int i = 0; i < my_WAV.ExtraParamSize / 4; i += 1) {
            my_WAV.ExtraParamString[i] = toString(2);
            fileIn.seekg(-4, std::ios_base::cur);
            my_WAV.ExtraParamLong[i] = toLong(2);
            std::cout << "  ExtraParam" << i + 1 << " : " << my_WAV.ExtraParamString[i];
            std::cout << "    " << my_WAV.ExtraParamLong[i] << std::endl;
        }


        surplus = my_WAV.BlocSize - (my_WAV.ExtraParamSize + 18);
        toLong(surplus);

    } else {
        surplus = my_WAV.BlocSize - 16;
        toLong(surplus);

    }
    if (surplus != 0) {
        std::cout << " !  !  ! surplus : " << surplus << " !  !  ! " << std::endl;
    }
    while (fileIn && toString(4) != "data") {
        fileIn.seekg(-4, std::ios_base::cur);
        std::cout << "  more : " << toString(4) << std::endl;

        fileIn.seekg(-3, std::ios_base::cur);
    }
    // GoTo "data"

    fileIn.seekg(-4, std::ios_base::cur);

// ====================================================
//    [Bloc des données]
// ====================================================

    std::cout << std::endl;

    my_WAV.DataBlocID = toString(4);
    std::cout << "      DataBlocID : " << my_WAV.DataBlocID << std::endl;
//  (4 octets) : Constante «data»  (0x64,0x61,0x74,0x61)

    my_WAV.DataSize = toLong(4);
    std::cout << "        DataSize : " << my_WAV.DataSize << std::endl;
//  (4 octets) : Nombre d'octets des données (c.-à-d. "Data[]", c.-à-d. taille_du_fichier - taille_de_l'entête  (qui fait 44 octets normalement).

    std::cout << std::endl;
    std::cout << std::endl;
}






void AudioFileWAV::getDataWAV() {

    if (fileIn) {

        std::cout << "  Reading " << my_WAV.DataSize << " bits of data ... ";

        int bufferLength = my_WAV.BitsPerSample / 8;
        char * buffer = new char[bufferLength];

        for (unsigned int j = 0; j < my_WAV.NbrCanaux; j += 1) {

            std::vector<unsigned char> tmp;
            for (unsigned int i = 0; i < my_WAV.DataSize / my_WAV.BytePerBloc ; i += 1) {

                //if (i % 1000 == 0)
                //    std::cout << "i : " << i << "   j : " << j << std::endl;

                fileIn.read(buffer, bufferLength);
                tmp.insert(tmp.end(), &buffer[0], &buffer[bufferLength]);
            }
            my_WAV.Data.push_back(tmp);
        }

        if (fileIn) {

            std::cout << "Done" << std::endl;
        } else {

            std::cout << "Error" << std::endl;
        }

        delete[] buffer;

    } else {

        std::cout << "fileIn closed : getDataWAV impossible" << std::endl;
    }

    std::cout << std::endl;

    fileIn.close();
}



void AudioFileWAV::updateAUDIO(){

    std::cout << "  WAV to AUDIO conversion ... ";

    my_AUDIO.FileTypeBlocID    =   my_WAV.FileTypeBlocID;
    my_AUDIO.FileSize          =   my_WAV.FileSize      ;
    my_AUDIO.FileFormatID      =   my_WAV.FileFormatID  ;

    my_AUDIO.FormatBlocID      =   my_WAV.FormatBlocID  ;
    my_AUDIO.BlocSize          =   my_WAV.BlocSize      ;

    my_AUDIO.AudioFormat       =   my_WAV.AudioFormat   ;
    my_AUDIO.NbrCanaux         =   my_WAV.NbrCanaux     ;
    my_AUDIO.Frequence         =   my_WAV.Frequence     ;
    my_AUDIO.BytePerSec        =   my_WAV.BytePerSec    ;
    my_AUDIO.BytePerBloc       =   my_WAV.BytePerBloc   ;
    my_AUDIO.BitsPerSample     =   my_WAV.BitsPerSample ;

    my_AUDIO.DataBlocID        =   my_WAV.DataBlocID    ;
    my_AUDIO.DataSize          =   my_WAV.DataSize      ;

    my_AUDIO.Data = uCharToIntArray(my_WAV.Data);

    std::cout << "Done" << std::endl;
}



void AudioFileWAV::updateWAV(){

    std::cout << "  AUDIO to WAV conversion ... ";

    my_WAV.FileTypeBlocID    =   my_AUDIO.FileTypeBlocID;
    my_WAV.FileSize          =   my_AUDIO.FileSize      ;
    my_WAV.FileFormatID      =   my_AUDIO.FileFormatID  ;

    my_WAV.FormatBlocID      =   my_AUDIO.FormatBlocID  ;
    my_WAV.BlocSize          =   my_AUDIO.BlocSize      ;

    my_WAV.AudioFormat       =   my_AUDIO.AudioFormat   ;
    my_WAV.NbrCanaux         =   my_AUDIO.NbrCanaux     ;
    my_WAV.Frequence         =   my_AUDIO.Frequence     ;
    my_WAV.BytePerSec        =   my_AUDIO.BytePerSec    ;
    my_WAV.BytePerBloc       =   my_AUDIO.BytePerBloc   ;
    my_WAV.BitsPerSample     =   my_AUDIO.BitsPerSample ;

    my_WAV.DataBlocID        =   my_AUDIO.DataBlocID    ;
    my_WAV.DataSize          =   my_AUDIO.DataSize      ;

    my_WAV.Data = intToUCharArray(my_AUDIO.Data);

    std::cout << "Done" << std::endl;
}



int AudioFileWAV::save() {
    std::cout << "  Preparing to create and save the file" << std::endl;

    findNameAndOpenOut();

    updateWAV();

    createFile();

    return 0;
}



void AudioFileWAV::createFile() {

    std::cout << "\tCreating the output file : "<< std::endl;
    std::cout << std::endl;

    char * buffer = new char [50];

    buffer = toChar(my_WAV.FileTypeBlocID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(my_WAV.FileSize, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(my_WAV.FileFormatID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(my_WAV.FormatBlocID, 4);
    fileOut.write(buffer, 4);

    my_WAV.BlocSize = 16;
    buffer = toChar(my_WAV.BlocSize, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(my_WAV.AudioFormat, 2);
    fileOut.write(buffer, 2);

    buffer = toChar(my_WAV.NbrCanaux, 2);
    fileOut.write(buffer, 2);

    buffer = toChar(my_WAV.Frequence, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(my_WAV.BytePerSec, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(my_WAV.BytePerBloc, 2);
    fileOut.write(buffer, 2);

    buffer = toChar(my_WAV.BitsPerSample, 2);
    fileOut.write(buffer, 2);


    if (my_WAV.AudioFormat != 1) {
        buffer = toChar(my_WAV.ExtraParamSize, 2);
        fileOut.write(buffer, 2);
    }
    // Other optional elements not supported yet

    buffer = toChar(my_WAV.DataBlocID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(my_WAV.DataSize, 4);
    fileOut.write(buffer, 4);

    std::cout << "so far so good ... ";




    int bufferLength = my_WAV.BitsPerSample / 8;
    int blocLength = bufferLength * my_WAV.NbrCanaux;

    delete[] buffer;
    buffer = new char[bufferLength];

    for (unsigned int i = 0; i < my_WAV.NbrCanaux; i += 1) {

        for (unsigned int j = 0; j < my_WAV.DataSize / blocLength; j += 1) {

            for (int k = 0; k < bufferLength; k += 1) {

/*
                if (i % 1000 == 0) {
                    std::cout << i << " " << j << " " << k << std::endl;
                }
*/

                buffer[k] = my_WAV.Data[i][j * bufferLength + k];
            }

            fileOut.write(buffer, bufferLength);
        }
    }

    std::cout << "  File created"<< std::endl;
    std::cout << " =================================================="<< std::endl;
    std::cout << std::endl;

    delete[] buffer;

    fileOut.close();
}

