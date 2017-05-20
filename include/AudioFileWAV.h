#ifndef AUDIOFILEWAV_H
#define AUDIOFILEWAV_H

#include "AudioFile.h"

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

    unsigned long ExtraParamSize;
    std::string * ExtraParamString;
    unsigned long * ExtraParamLong;

    std::string DataBlocID;
    unsigned long DataSize;

    char ** Data;

} WAV;


class AudioFileWAV : public AudioFile
{
    public:
        AudioFileWAV();
        AudioFileWAV(std::string name);
        virtual ~AudioFileWAV();

        void readWAV();
        void readHeaderWAV();
        void getDataWAV();

        void updateAUDIO();
        void updateAUDIO(WAV w, AUDIO a);
        void updateAUDIO(AUDIO a, WAV w);

        void updateWAV();
        void updateWAV(WAV w, AUDIO a);
        void updateWAV(AUDIO a, WAV w);

        void createWAV(WAV input_WAV);
        void createWAV();

        int clone() override;
        int save() override;

        //void applyEffect();


    protected:

    private:

        WAV original_WAV;
        WAV created_WAV;
};

#endif // AUDIOFILEWAV_H
