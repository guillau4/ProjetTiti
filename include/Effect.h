#ifndef EFFECT_H
#define EFFECT_H

#include "Formats.h"


class Effect
{
    public:
        Effect();
        virtual ~Effect();

        static void echo(AUDIO * a, double seconds, double factor);

        static void delay(AUDIO * a, double seconds);

        static void gain (AUDIO * a, double factor);

        static void add1sec (AUDIO * a);

    protected:

    private:
};

#endif // EFFECT_H
