#ifndef FORMATS_H
#define FORMATS_H

#include <string>

struct AUDIO {

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

    int ** Data;

};


struct WAV {

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

    unsigned long ExtraParamSize;
    std::string * ExtraParamString;
    unsigned long * ExtraParamLong;

    std::string DataBlocID;
    unsigned long DataSize;

    unsigned char ** Data;

};


#endif // FORMATS_H
