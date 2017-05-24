#ifndef AUDIOFILEWAV_H
#define AUDIOFILEWAV_H

#include <assert.h>

#include "Formats.h"
#include "ConsoleStream.h"
#include "AudioFile.h"



class AudioFileWAV : public AudioFile
{
    public:
        AudioFileWAV(std::string name);
        virtual ~AudioFileWAV();

        void readWAV();
        void readHeaderWAV();
        void getDataWAV();

        void updateAUDIO();
        void updateWAV();

        int save() override;
        void createFile() override;


    protected:

    private:

        WAV my_WAV;
};

#endif // AUDIOFILEWAV_H
