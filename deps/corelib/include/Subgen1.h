#pragma once

#include "Subgen.h"

extern bool   _Subgen1Inited;
extern Subgen _Subgen1Instance;

inline void _Subgen1Init()
{
    if (!_Subgen1Inited) return;
    _Subgen1Inited = false;
    _Subgen1Instance = SubgenCreate(0);
}

inline int Subgen1Next()
{
    _Subgen1Init();
    return SubgenNext(&_Subgen1Instance);
}
inline float Subgen1FractionUnsigned()
{
    _Subgen1Init();
    return SubgenFractionUnsigned(&_Subgen1Instance);
}
inline float Subgen1FractionSigned()
{
    _Subgen1Init();
    return SubgenFractionSigned(&_Subgen1Instance);
}
inline float Subgen1Range(float min, float max)
{
    _Subgen1Init();
    return SubgenRange(&_Subgen1Instance, min , max);
}
