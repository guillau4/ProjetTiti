#ifndef EFFECT_H
#define EFFECT_H

#include <assert.h>

#include "Formats.h"


class Effect
{
    public:
        Effect();
        virtual ~Effect();

        static void echo(AUDIO * a, double seconds, double factor, int number = 10);

        static void add(AUDIO * a, AUDIO * b);

        static void delay(AUDIO * a, double seconds);

        static void gain (AUDIO * a, double factor);

        static void add1sec (AUDIO * a);

    protected:

    private:
};

#endif // EFFECT_H
