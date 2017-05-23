#ifndef EFFECT_H
#define EFFECT_H

#include "Formats.h"


class Effect
{
    public:
        Effect();
        virtual ~Effect();

        static AUDIO echo(double seconds, double factor, AUDIO input);

        static AUDIO delay(double seconds, AUDIO input);

        static AUDIO gain (double factor, AUDIO input);

    protected:

    private:
};

#endif // EFFECT_H
