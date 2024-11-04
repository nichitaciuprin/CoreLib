#pragma once

// https://rosettacode.org/wiki/Subtractive_generator#C
// https://www.pcg-random.org/download.html

#if RAND_MAX == 32767
#define Rand32() ((rand() << 16) + (rand() << 1) + (rand() & 1))
#else
#define Rand32() rand()
#endif

class Subgen
{
public:
    static Subgen staticSubgen;
    static int StaticNext()
    {
        return staticSubgen.Next();
    }

    Subgen(int seed)
    {
        si = 0;
        sj = 24;
        seed = seed;
        int p2 = 1;
        state[0] = seed % MAX;
        for (int i = 1, j = 21; i < 55; i++, j += 21)
        {
            if (j >= 55) j -= 55;
            state[j] = p2;
            p2 = seed - p2;
            if (p2 < 0) p2 += MAX;
            seed = state[j];
        }
        for (int i = 0; i < 165; i++)
            Next();
    }
    int Next()
    {
        if (!si--) si = 54;
        if (!sj--) sj = 54;
        int x = state[si] - state[sj];
        if (x < 0) x += MAX;
        state[si] = x;
        return x;
    }
    float FractionUnsigned()
    {
        return Next() / (float)MAX;
    }
    float FractionSigned()
    {
        return FractionUnsigned() * 2 - 1;
    }
    float Range(float min, float max)
    {
        return min + (max - min) * FractionUnsigned();
    }
private:
    int state[55];
    int si;
    int sj;
    int seed;
    int MAX = 1000000000;
};

Subgen Subgen::staticSubgen = Subgen(0);