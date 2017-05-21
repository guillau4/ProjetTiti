#include "Effect.h"
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

    std::cout << nbC << " " << nbB << " " << nbS << std::endl;

    output.FileSize += byte_delay;
    output.DataSize += byte_delay;

    output.Data = new int * [nbC];
    for (unsigned int i = 0; i < nbC; i += 1) {
        output.Data[i] = new int [nbB + byte_delay];
    }

    for (unsigned int i = 0; i < byte_delay; i += 1) {
        for (unsigned int j = 0; j < nbC; j += 1) {

            output.Data[j][i] = 0;
        }
    }

    for (unsigned int i = 0; i < nbB; i += 1) {
        for (unsigned int j = 0; j < nbC; j += 1) {
            if (i % 1000 == 0) {
                std::cout << i+byte_delay << " " << j << std::endl;
            }
            output.Data[j][i + byte_delay] = input.Data[j][i];
        }
    }

    return output;

}
