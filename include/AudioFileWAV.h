#ifndef AUDIOFILEWAV_H
#define AUDIOFILEWAV_H

#include "Formats.h"
#include "AudioFile.h"



class AudioFileWAV : public AudioFile
{
    public:
        AudioFileWAV();
        AudioFileWAV(std::string name);
        virtual ~AudioFileWAV();

        void readWAV();
        void readHeaderWAV();
        void getDataWAV();

        AUDIO updateAUDIO();
        AUDIO updateAUDIO(WAV w);

        WAV updateWAV();
        WAV updateWAV(AUDIO a);

        void createWAV(WAV input_WAV);
        void createWAV();

        int save() override;

        //void applyEffect();


    protected:

    private:

        WAV original_WAV;
        WAV created_WAV;
};

#endif // AUDIOFILEWAV_H
