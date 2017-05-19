#include "AudioFileWAV.h"

AudioFileWAV::AudioFileWAV()
{
    //ctor
}

AudioFileWAV::AudioFileWAV(std::string name) :
AudioFile(name, ".wav", "wav\\", "created\\"){

    readWAV();
    createWAV();

}



AudioFileWAV::~AudioFileWAV()
{
    // Should make sure the files are closed
}




void AudioFileWAV::readWAV() {

    std::cout << " =================================================="<< std::endl;
    std::cout << "\tReading inFile header : "<< std::endl;
    std::cout << std::endl;
    readHeaderWAV();
// original_WAV updated

    std::cout << "\tReading inFile data : "<< std::endl;
    std::cout << std::endl;
    getDataWAV();
// *original_WAV.DataSize* bytes of data

    created_WAV = original_WAV;
}





void AudioFileWAV::readHeaderWAV(){


    fileIn.seekg (0, fileIn.beg);


// ====================================================
//    [Bloc de déclaration d'un fichier au format WAVE]
// ====================================================

    original_WAV.FileTypeBlocID = toString(4);
    std::cout << "  FileTypeBlocID : " << original_WAV.FileTypeBlocID << std::endl;
//  (4 octets) : Constante «RIFF»  (0x52,0x49,0x46,0x46)

    original_WAV.FileSize = toLong(4);
    std::cout << "  FileSize       : " << original_WAV.FileSize << std::endl;
//  (4 octets) : Taille du fichier moins 8 octets

    original_WAV.FileFormatID = toString(4);
    std::cout << "  FileFormatID   : " << original_WAV.FileFormatID << std::endl;
//  (4 octets) : Format = «WAVE»  (0x57,0x41,0x56,0x45)

// ====================================================
//    [Bloc décrivant le format audio]
// ====================================================

    std::cout << std::endl;

    original_WAV.FormatBlocID = toString(4);
    std::cout << "  FormatBlocID   : " << original_WAV.FormatBlocID << std::endl;
//  (4 octets) : Identifiant «fmt »  (0x66,0x6D, 0x74,0x20)

    original_WAV.BlocSize = toLong(4);
    std::cout << "  BlocSize       : " << original_WAV.BlocSize << std::endl;
//  (4 octets) : Nombre d'octets du bloc - 16  (0x10)

    original_WAV.AudioFormat = toLong(2);
    std::cout << "  AudioFormat    : " << original_WAV.AudioFormat << std::endl;
//  (2 octets) : Format du stockage dans le fichier (1: PCM, ...)

    original_WAV.NbrCanaux = toLong(2);
    std::cout << "  NbrCanaux      : " << original_WAV.NbrCanaux << std::endl;
//  (2 octets) : Nombre de canaux (de 1 à 6, cf. ci-dessous)

    original_WAV.Frequence = toLong(4);
    std::cout << "  Frequence      : " << original_WAV.Frequence << std::endl;
//  (4 octets) : Fréquence d'échantillonnage (en hertz) [Valeurs standardisées : 11025, 22050, 44100 et éventuellement 48000 et 96000]

    original_WAV.BytePerSec = toLong(4);
    std::cout << "  BytePerSec     : " << original_WAV.BytePerSec << std::endl;
//  (4 octets) : Nombre d'octets à lire par seconde (c.-à-d., Frequence * BytePerBloc).

    original_WAV.BytePerBloc = toLong(2);
    std::cout << "  BytePerBloc    : " << original_WAV.BytePerBloc << std::endl;
//  (2 octets) : Nombre d'octets par bloc d'échantillonnage (c.-à-d., tous canaux confondus : NbrCanaux * BitsPerSample/8).

    original_WAV.BitsPerSample = toLong(2);
    std::cout << "  BitsPerSample  : " << original_WAV.BitsPerSample << std::endl;
//  (2 octets) : Nombre de bits utilisés pour le codage de chaque échantillon (8, 16, 24)

// ====================================================
//    [Bloc des données]
// ====================================================

    std::cout << std::endl;

    original_WAV.DataBlocID = toString(4);
    std::cout << "  DataBlocID     : " << original_WAV.DataBlocID << std::endl;
//  (4 octets) : Constante «data»  (0x64,0x61,0x74,0x61)

    original_WAV.DataSize = toLong(4);
    std::cout << "  DataSize       : " << original_WAV.DataSize << std::endl;
//  (4 octets) : Nombre d'octets des données (c.-à-d. "Data[]", c.-à-d. taille_du_fichier - taille_de_l'entête  (qui fait 44 octets normalement).

    std::cout << std::endl;
    std::cout << std::endl;
}






void AudioFileWAV::getDataWAV() {

    original_WAV.Data = new char [original_WAV.DataSize];
    if (fileIn) {

        std::cout << "  Reading " << original_WAV.DataSize << " bits of data ...";
        fileIn.read(original_WAV.Data, original_WAV.DataSize);

        if (fileIn) {

            std::cout << "Done" << std::endl;
        } else {

            std::cout << "Error" << std::endl;
        }
    } else {

        std::cout << "fileIn closed : getDataWAV impossible" << std::endl;
    }

    std::cout << std::endl;
}


void AudioFileWAV::createWAV() {

    createWAV(created_WAV);
}


void AudioFileWAV::createWAV(WAV input_WAV) {

    std::cout << "\tCreating the output file : "<< std::endl;
    std::cout << std::endl;

    char * buffer = new char [4];

    buffer = toChar(input_WAV.FileTypeBlocID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.FileSize, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.FileFormatID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.FormatBlocID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.BlocSize, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.AudioFormat, 2);
    fileOut.write(buffer, 2);

    buffer = toChar(input_WAV.NbrCanaux, 2);
    fileOut.write(buffer, 2);

    buffer = toChar(input_WAV.Frequence, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.BytePerSec, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.BytePerBloc, 2);
    fileOut.write(buffer, 2);

    buffer = toChar(input_WAV.BitsPerSample, 2);
    fileOut.write(buffer, 2);

    buffer = toChar(input_WAV.DataBlocID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.DataSize, 4);
    fileOut.write(buffer, 4);

    fileOut.write(input_WAV.Data, input_WAV.DataSize);

    std::cout << "  File created"<< std::endl;
    std::cout << " =================================================="<< std::endl;
    std::cout << std::endl;

}


/*
void AudioFileWAV::applyEffect() {

    created_WAV = delayWAV(5);

    for (int i = 0; i < original_WAV.DataSize; i += 1) {
        created_WAV.Data[i] = original_WAV.Data[i];
    }
}
*/

