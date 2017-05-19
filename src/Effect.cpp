#include "Effect.h"

Effect::Effect()
{
    //ctor
}

Effect::~Effect()
{
    //dtor
}

/*

WAV AudioFile::echo(double seconds, double factor, WAV input_WAV) {

    return input_WAV;
}


WAV AudioFile::echoWAV(double seconds, double factor) {

    return echo(seconds, factor, original_WAV);
}


WAV AudioFile::delay(double seconds, WAV input_WAV) {
    WAV output_WAV = input_WAV;

    unsigned long byte_delay = (unsigned long) (seconds * input_WAV.BytePerSec);

    output_WAV.FileSize += byte_delay;
    output_WAV.DataSize += byte_delay;

    output_WAV.Data = new char [output_WAV.DataSize];

    for (unsigned int i = 0; i < byte_delay; i += 1) {

        output_WAV.Data[i] = 0;
    }

    for (unsigned int i = 0; i < output_WAV.DataSize - byte_delay; i += 1) {

        output_WAV.Data[i + byte_delay] = input_WAV.Data[i];
    }

    return output_WAV;

}


WAV AudioFile::delayWAV(double seconds) {

    return delay(seconds, original_WAV);
} */
