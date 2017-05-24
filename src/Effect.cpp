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



void Effect::echo(AUDIO * a, double seconds, double factor) {

}


void Effect::delay(AUDIO * a, double seconds) {

    unsigned long byte_delay = (unsigned long) (seconds * a->BytePerSec);

    a->FileSize += byte_delay;
    a->DataSize += byte_delay;

    for (unsigned int i = 0; i < a->Data.size(); i += 1) {

        a->Data[i].insert(a->Data[i].begin(), byte_delay, 0);
    }
}

void Effect::gain (AUDIO * a, double factor){

    double amplified;

    for (unsigned int i = 0; i < a->Data.size(); i++){
        for(unsigned int j = 0; j < a->Data[i].size(); j++){

            amplified = factor * a->Data[i][j];

            if (amplified > 32766){
                amplified = 32766;

            } else if(amplified < -32766){
                amplified = -32766;

            }
            a->Data[i][j] = amplified;
        }
    }
}

void Effect::add1sec(AUDIO * a) {

    unsigned long byte_add = (unsigned long) (a->BytePerSec);

    a->FileSize += byte_add;
    a->DataSize += byte_add;

    for (unsigned int i = 0; i < a->Data.size(); i += 1) {

        a->Data[i].insert(a->Data[i].end(), byte_add, 0);
    }
}
