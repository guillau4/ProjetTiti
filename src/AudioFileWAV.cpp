#include "AudioFileWAV.h"

AudioFileWAV::AudioFileWAV()
{
    //ctor
}

AudioFileWAV::AudioFileWAV(std::string name) :
AudioFile(name, ".wav", "wav\\", "created\\"){

    readWAV();

    //updateAUDIO();

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
    std::cout << "        FileSize : " << original_WAV.FileSize << std::endl;
//  (4 octets) : Taille du fichier moins 8 octets

    original_WAV.FileFormatID = toString(4);
    std::cout << "    FileFormatID : " << original_WAV.FileFormatID << std::endl;
//  (4 octets) : Format = «WAVE»  (0x57,0x41,0x56,0x45)

// ====================================================
//    [Bloc décrivant le format audio]
// ====================================================

    std::cout << std::endl;

    original_WAV.FormatBlocID = toString(4);
    std::cout << "    FormatBlocID : " << original_WAV.FormatBlocID << std::endl;
//  (4 octets) : Identifiant «fmt »  (0x66,0x6D, 0x74,0x20)

    original_WAV.BlocSize = toLong(4);
    std::cout << "        BlocSize : " << original_WAV.BlocSize << std::endl;
//  (4 octets) : Nombre d'octets du bloc - 16  (0x10)

    original_WAV.AudioFormat = toLong(2);
    std::cout << "     AudioFormat : " << original_WAV.AudioFormat << std::endl;
//  (2 octets) : Format du stockage dans le fichier (1: PCM, ...)

    original_WAV.NbrCanaux = toLong(2);
    std::cout << "       NbrCanaux : " << original_WAV.NbrCanaux << std::endl;
//  (2 octets) : Nombre de canaux (de 1 à 6, cf. ci-dessous)

    original_WAV.Frequence = toLong(4);
    std::cout << "       Frequence : " << original_WAV.Frequence << std::endl;
//  (4 octets) : Fréquence d'échantillonnage (en hertz) [Valeurs standardisées : 11025, 22050, 44100 et éventuellement 48000 et 96000]

    original_WAV.BytePerSec = toLong(4);
    std::cout << "      BytePerSec : " << original_WAV.BytePerSec << std::endl;
//  (4 octets) : Nombre d'octets à lire par seconde (c.-à-d., Frequence * BytePerBloc).

    original_WAV.BytePerBloc = toLong(2);
    std::cout << "     BytePerBloc : " << original_WAV.BytePerBloc << std::endl;
//  (2 octets) : Nombre d'octets par bloc d'échantillonnage (c.-à-d., tous canaux confondus : NbrCanaux * BitsPerSample/8).

    original_WAV.BitsPerSample = toLong(2);
    std::cout << "   BitsPerSample : " << original_WAV.BitsPerSample << std::endl;
//  (2 octets) : Nombre de bits utilisés pour le codage de chaque échantillon (8, 16, 24)

// ====================================================
//    [Bloc optionnel]
// ====================================================
    int surplus;

    if (original_WAV.AudioFormat != 1) {
        original_WAV.ExtraParamSize = toLong(2);
        std::cout << "  ExtraParamSize : " << original_WAV.ExtraParamSize << std::endl;
//  (2 octets) : Utilisé lorsque le format de stockage de data n'est pas en PCM linéaire

        original_WAV.ExtraParamString = new std::string [original_WAV.ExtraParamSize / 4];
        original_WAV.ExtraParamLong = new unsigned long [original_WAV.ExtraParamSize / 4];

        for (int i = 0; i < original_WAV.ExtraParamSize / 4; i += 1) {
            original_WAV.ExtraParamString[i] = toString(2);
            fileIn.seekg(-4, std::ios_base::cur);
            original_WAV.ExtraParamLong[i] = toLong(2);
            std::cout << "  ExtraParam" << i + 1 << " : " << original_WAV.ExtraParamString[i];
            std::cout << "    " << original_WAV.ExtraParamLong[i] << std::endl;
        }


        surplus = original_WAV.BlocSize - (original_WAV.ExtraParamSize + 18);
        toLong(surplus);

    } else {
        surplus = original_WAV.BlocSize - 16;
        toLong(surplus);

    }
    std::cout << "  surplus : " << surplus << std::endl;

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

    original_WAV.DataBlocID = toString(4);
    std::cout << "      DataBlocID : " << original_WAV.DataBlocID << std::endl;
//  (4 octets) : Constante «data»  (0x64,0x61,0x74,0x61)

    original_WAV.DataSize = toLong(4);
    std::cout << "        DataSize : " << original_WAV.DataSize << std::endl;
//  (4 octets) : Nombre d'octets des données (c.-à-d. "Data[]", c.-à-d. taille_du_fichier - taille_de_l'entête  (qui fait 44 octets normalement).

    std::cout << std::endl;
    std::cout << std::endl;
}






void AudioFileWAV::getDataWAV() {

    original_WAV.Data = new char * [original_WAV.NbrCanaux];

    for (int i = 0; i < original_WAV.NbrCanaux; i += 1) {
        original_WAV.Data[i] = new char [original_WAV.DataSize / original_WAV.NbrCanaux];

    }

    if (fileIn) {

        std::cout << "  Reading " << original_WAV.DataSize << " bits of data ...";

        int bufferLength = original_WAV.BitsPerSample / 8;
        int blocLength = bufferLength * original_WAV.NbrCanaux;

        char * buffer = new char[bufferLength];
        for (int i = 0; i < original_WAV.DataSize / blocLength ; i += 1) {
            // i : bloc (all channels) = blocLength

            for (int j = 0; j < original_WAV.NbrCanaux; j += 1) {
                // j : sample (one channel) = bufferLength

                fileIn.read(buffer, bufferLength);
                for (int k = 0; k < bufferLength; k += 1) {
                    // k : byte = 1

                    //if (i % 1000 == 0)
                    //    std::cout << "i : " << i << "   j : " << j << "   k : " << k << std::endl;

                    original_WAV.Data[j][i * bufferLength + k] = buffer[k];
                }
            }
        }

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




void AudioFileWAV::updateAUDIO(){
    updateAUDIO(original_WAV, audioIn);
    updateAUDIO(created_WAV, audioOut);
}


void AudioFileWAV::updateAUDIO(AUDIO a, WAV w){
    updateAUDIO(w, a);
}

void AudioFileWAV::updateAUDIO(WAV w, AUDIO a){

    a.FileSize      =   w.FileSize      ;
    a.FileFormatID  =   w.FileFormatID  ;

    a.FormatBlocID  =   w.FormatBlocID  ;
    a.BlocSize      =   w.BlocSize      ;

    a.AudioFormat   =   w.AudioFormat   ;
    a.NbrCanaux     =   w.NbrCanaux     ;
    a.Frequence     =   w.Frequence     ;
    a.BytePerSec    =   w.BytePerSec    ;
    a.BytePerBloc   =   w.BytePerBloc   ;
    a.BitsPerSample =   w.BitsPerSample ;

    a.DataBlocID    =   w.DataBlocID    ;
    a.DataSize      =   w.DataSize      ;

    a.Data = deepCopy(w.Data, w.NbrCanaux, w.DataSize / w.BytePerBloc);

}



void AudioFileWAV::updateWAV(){
    updateWAV(original_WAV, audioIn);
    updateWAV(created_WAV, audioOut);
}


void AudioFileWAV::updateWAV(AUDIO a, WAV w){
    updateWAV(w, a);
}

void AudioFileWAV::updateWAV(WAV w, AUDIO a){

    w.FileSize      =   a.FileSize      ;
    w.FileFormatID  =   a.FileFormatID  ;

    w.FormatBlocID  =   a.FormatBlocID  ;
    w.BlocSize      =   a.BlocSize      ;

    w.AudioFormat   =   a.AudioFormat   ;
    w.NbrCanaux     =   a.NbrCanaux     ;
    w.Frequence     =   a.Frequence     ;
    w.BytePerSec    =   a.BytePerSec    ;
    w.BytePerBloc   =   a.BytePerBloc   ;
    w.BitsPerSample =   a.BitsPerSample ;

    w.DataBlocID    =   a.DataBlocID    ;
    w.DataSize      =   a.DataSize      ;

    w.Data = deepCopy(a.Data, a.NbrCanaux, a.DataSize / a.BytePerBloc);
    // Why copy the address rather than the values ?

}


int AudioFileWAV::clone() {
    std::cout << "  Cloning the WAV" << std::endl;

    int dim1 = original_WAV.NbrCanaux,
        dim2 = original_WAV.DataSize / original_WAV.BytePerBloc;

    created_WAV = original_WAV;
    created_WAV.Data = deepCopy(original_WAV.Data, dim1, dim2);

    updateAUDIO();

    return 0;
}


int AudioFileWAV::save() {
    std::cout << "  Preparing to create and save the file" << std::endl;

    findNameAndOpenOut();

    createWAV(created_WAV);

    return 0;
}


void AudioFileWAV::createWAV() {

    createWAV(created_WAV);
}


void AudioFileWAV::createWAV(WAV input_WAV) {

    std::cout << "\tCreating the output file : "<< std::endl;
    std::cout << std::endl;

    char * buffer = new char [50];

    buffer = toChar(input_WAV.FileTypeBlocID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.FileSize, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.FileFormatID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.FormatBlocID, 4);
    fileOut.write(buffer, 4);

    input_WAV.BlocSize = 16;
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


    if (input_WAV.AudioFormat != 1) {
        buffer = toChar(input_WAV.ExtraParamSize, 2);
        fileOut.write(buffer, 2);
    }
    // Other optional elements not supported yet

    buffer = toChar(input_WAV.DataBlocID, 4);
    fileOut.write(buffer, 4);

    buffer = toChar(input_WAV.DataSize, 4);
    fileOut.write(buffer, 4);




    int bufferLength = input_WAV.BitsPerSample / 8;
    int blocLength = bufferLength * input_WAV.NbrCanaux;

    delete[] buffer;
    buffer = new char[bufferLength];

    for (int i = 0; i < input_WAV.DataSize / blocLength; i += 1) {
        // i : bloc (all channels) = blocLength

        for (int j = 0; j < input_WAV.NbrCanaux; j += 1) {
            // j : sample (one channel) = bufferLength

            for (int k = 0; k < bufferLength; k += 1) {
                // k : byte = 1

                buffer[k] = input_WAV.Data[j][i * bufferLength + k];
            }

            fileOut.write(buffer, bufferLength);
        }
    }

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

