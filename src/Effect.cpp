#include "../include/Effect.h"
#include <iostream>

Effect::Effect()
{
    //ctor
}

Effect::~Effect()
{
    //dtor
}



AUDIO Effect::echo(double seconds, double factor, AUDIO input) {

    AUDIO output = input;

    return output;
}


AUDIO Effect::delay(double seconds, AUDIO input) {

    AUDIO output = input;

    unsigned long byte_delay = (unsigned long) (seconds * input.BytePerSec);
    unsigned int nbC = input.NbrCanaux;
    unsigned int nbB = input.DataSize / input.BytePerBloc;
    unsigned int nbS = nbB * nbC;

    //std::cout << nbC << " " << nbB << " " << nbS << std::endl;

    output.FileSize += byte_delay;
    output.DataSize += byte_delay;

    for (unsigned int i = 0; i < nbC; i += 1) {

        output.Data[i].insert(output.Data[i].begin(), byte_delay, 0);
    }

    return output;

}
