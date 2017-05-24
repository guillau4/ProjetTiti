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



void Effect::echo(AUDIO * a, double seconds, double factor, int number) {

    AUDIO b = * a;

    for (int i = 0; i < number; i += 1) {
        delay(&b, seconds);
        gain(&b, factor);
        add(a, &b);
    }

}


void Effect::add(AUDIO * a, AUDIO * b) {
    assert (a->Data.size() == b->Data.size());

    int dimA = a->Data[0].size(),
        dimB = b->Data[0].size();


    if (dimA < dimB) {

        AUDIO c = * b;
        add(&c, a);
        * a = c;

    } else {

        for (int i = 0; i < a->Data.size(); i += 1) {

            for (int j = 0; j < dimB; j += 1) {
                a->Data[i][j] += b->Data[i][j];
            }
        }
    }
}


void Effect::delay(AUDIO * a, double seconds) {

    unsigned long byte_delay = (unsigned long) (seconds * a->BytePerSec);

    a->FileSize += byte_delay;
    a->DataSize += byte_delay;

    for (unsigned long i = 0; i < a->Data.size(); i += 1) {

        a->Data[i].insert(a->Data[i].begin(), byte_delay / a->BytePerBloc, 0);
    }
}

void Effect::gain (AUDIO * a, double factor){

    for (unsigned long i = 0; i < a->Data.size(); i++){
        for(unsigned long j = 0; j < a->Data[i].size(); j++){

            a->Data[i][j] = factor * a->Data[i][j];
        }
    }
}

void Effect::add1sec(AUDIO * a) {

    unsigned long byte_add = (unsigned long) (a->BytePerSec);

    a->FileSize += byte_add;
    a->DataSize += byte_add;

    for (unsigned long i = 0; i < a->Data.size(); i += 1) {

        a->Data[i].insert(a->Data[i].end(), byte_add / a->BytePerBloc, 0);
    }
}
